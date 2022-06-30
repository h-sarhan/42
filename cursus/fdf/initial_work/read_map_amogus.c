/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/30 18:08:27 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotX(t_point *p, float x, float y, float z, float rot)
{
	p->x = x;
	p->y = cos(rot) * y - sin(rot) * z;
	p->z = -sin(rot) * y + cos(rot) * z;
}

void	rotY(t_point *p, float x, float y, float z, float rot)
{
	p->x = x * cos(rot) + sin(cos(rot)) * z;
	p->y = y;
	p->z = -sin(rot) * x + cos(rot) * z;
}

void	rotZ(t_point *p, float x, float y, float z, float rot)
{
	p->x = x * cos(rot) - sin(cos(rot)) * y;
	p->y = x * sin(rot) + cos(rot) * y;
	p->z = z;
}

void project_point(t_point *p, int x, int y, int z, int scale, int translate)
{
	float	beta;
	float	alpha;

	beta = 45 * (M_PI / 180.0f);
	alpha = asin(tan(30 * (M_PI / 180.0f)));   
	p->x = x * scale;
	p->y = y * scale;
	p->z = z * scale;
	rotX(p, p->x, p->y, p->z, beta);
	rotZ(p, p->x, p->y, p->z, alpha + 15 * (M_PI / 180.0f));
	// rotZ(p, p->x, p->y, p->z, alpha);
}

void	free_split_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_lines(void *split_array)
{
	free_split_array(split_array);
}

t_map	*read_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	int		**z_values;
	t_map	*map;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	tokens = ft_split(line, ' ');
	int i = 0;
	while (tokens[i] != NULL)
		i++;
	int num_cols = 27;
	free_split_array(tokens);	
	lines = NULL;
	num_rows = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		num_rows++;
		line = get_next_line(fd);
	}
	num_rows = 29;
	first = lines;
	z_values = ft_calloc(num_rows + 1, sizeof(int *));
	z_values[num_rows] = NULL;
	i = 0;
	int j = 0;
	while (i < num_rows)
	{
		z_values[i] = ft_calloc(num_cols + 1, sizeof(int));
		line = lines->content;
		tokens = ft_split(line, ' ');
		j = 0;
		while (j < num_cols)
		{
			z_values[i][j] = atoi(tokens[j]);
			j++;
		}
		lines = lines->next;
		free_split_array(tokens);
		i++;
	}
	map = ft_calloc(1, sizeof(t_map));
	map->z_values = z_values;
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	map->min_xval = INT_MAX;
	map->min_yval = INT_MAX;
	map->max_xval = INT_MIN;
	map->max_yval = INT_MIN;
	ft_lstclear(&first, free);
	return (map);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	remap_points(t_map *map, int translate, int scale)
{
	int i = 0;
	int j = 0;

	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->min_xval < 0)
				map->points[i][j]->x -= map->min_xval;
			if (map->min_yval < 0)
				map->points[i][j]->y -= map->min_yval;
			j++;
		}
		i++;
	}
	if (map->min_xval < 0)
	{
		map->max_xval -= map->min_xval;
		map->min_xval = 0;
	}
	if (map->min_yval < 0)
	{
		map->max_yval -= map->min_yval;
		map->min_yval = 0;
	}
}

void	create_points(t_map *map, int scale, int translate)
{
	t_point	***points;
	int		i;
	int		j;

	i = 0;
	j = 0;
	points = ft_calloc(map->num_rows + 1, sizeof(t_point **));
	while (i < map->num_rows)
	{
		j = 0;
		points[i] = ft_calloc(map->num_cols + 1, sizeof(t_point *));
		while (j < map->num_cols)
		{
			points[i][j] = ft_calloc(1, sizeof(t_point));
			project_point(points[i][j],  i, map->num_cols - j, map->z_values[i][j], scale, translate);
			// project_point(points[i][j],  i,  j, map->z_values[i][j], scale, translate);
			if (points[i][j]->x < map->min_xval)
				map->min_xval = points[i][j]->x;	
			if (points[i][j]->y < map->min_yval)
				map->min_yval = points[i][j]->y;	
			if (points[i][j]->x > map->max_xval)
				map->max_xval = points[i][j]->x;	
			if (points[i][j]->y > map->max_yval)
				map->max_yval = points[i][j]->y;	
			j++;
		}
		i++;
	}
	map->points = points;
	remap_points(map, translate, scale);
}

void	free_map(t_map *map)
{
	int **zs = map->z_values;
	int i = 0;
	while (i < map->num_rows)
	{
		free(zs[i]);
		i++;
	}
	free(zs);
	map->z_values = NULL;
	i = 0;
	int j = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			free(map->points[i][j]);
			j++;
		}
		free(map->points[i]);
		i++;
	}
	free(map->points);
	free(map);
}

#include <time.h>
int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	clock_t t;
    t = clock();
	t_map	*map = read_map(argv[1]);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("read_map() took %f seconds to execute \n", time_taken);
	
	int scale = atoi(argv[2]);
	int i = 0;
	int j = 0;
	
	t = clock();
	create_points(map, scale, 0);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("create_points() took %f seconds to execute \n", time_taken);
	
	int translate = 20;
	mlx_win = mlx_new_window(mlx, map->max_xval + translate + 1, map->max_yval + translate + 1, "fdf");
	img.img = mlx_new_image(mlx, map->max_xval + translate + 1, map->max_yval + translate + 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t = clock();
	t_point ***points = map->points;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (j + 1 < map->num_cols)
				draw_line(&img, translate + points[i][j]->x, translate +  points[i][j]->y, translate +  points[i][j + 1]->x, translate +  points[i][j + 1]->y, 0x00FFFFFF);
			if (i + 1 < map->num_rows)
				draw_line(&img, translate + points[i][j]->x, translate +  points[i][j]->y, translate +  points[i + 1][j]->x, translate +  points[i + 1][j]->y, 0x00FFFFFF);
			j++;
		}
		i++;
	}
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("draw_points() took %f seconds to execute \n", time_taken);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_map(map);
}
