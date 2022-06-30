/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/30 09:56:32 by hsarhan          ###   ########.fr       */
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
	
	p->x = x;
	p->y = y;
	p->z = z;
	// rotZ(p, x * scale, y * scale, z * scale, beta);
	// rotX(p, p->x, p->y, p->z, alpha + 30 * (M_PI / 180.0f));
	rotZ(p, p->x, p->y, p->z, beta);
	// rotY(p, p->x, p->y, p->z, 10 * (M_PI / 180.0f));
	rotX(p, p->x, p->y, p->z, alpha + 30 * (M_PI / 180.0f));
	// rotX(p, p->x, p->y, p->z, 30 * (M_PI / 180.0f));
	// // rotX(p, p->x, p->y, p->z, 90 * (M_PI / 180.0f));
	// p->x += translate;
	// p->y += translate;
}

t_map	*read_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	int		num_rows;
	int		**z_values;
	t_map	*map;
	
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	tokens = ft_split(line, ' ');
	int i = 0;
	while (tokens[i] != NULL)
		i++;
	int num_cols = i;
	lines = NULL;

	num_rows = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		num_rows++;
		line = get_next_line(fd);
	}
	z_values = ft_calloc(num_rows + 1, sizeof(int *));
	i = 0;
	int j = 0;
	while (i < num_rows)
	{
		z_values[i] = ft_calloc(num_cols + 1, sizeof(int));
		j = 0;
		while (j < num_cols)
		{
			line = lines->content;
			tokens = ft_split(line, ' ');
			z_values[i][j] = atoi(tokens[j]);
			j++;
		}
		lines = lines->next;
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
	// printf("SEG\n");
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

	printf("MAX_XVAL%d\n", map->max_xval);
	printf("MIN_XVAL%d\n", map->min_xval);
	printf("MAX_YVAL%d\n", map->max_yval);
	printf("MIN_YVAL%d\n", map->min_yval);
	printf("SCALE == %d\n", scale);
	// if (map->min_xval < 0 || map->min_yval < 0)
	// {
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->min_xval < 0)
				map->points[i][j]->x -= map->min_xval;
			if (map->min_yval < 0)
				map->points[i][j]->y -= map->min_yval;
			map->points[i][j]->x *= scale;
			map->points[i][j]->y *= scale;
			if (map->points[i][j]->x < 0)
			{
				printf("THIS SHOULD NOT HAPPEN\n");
				printf("POINT x==%d\n", map->points[i][j]->x);
				printf("POINT y==%d\n", map->points[i][j]->y);
			}
			if (map->points[i][j]->y < 0)
				printf("THIS SHOULD NOT HAPPEN\n");
			// map->points[i][j]->x += translate;
			// map->points[i][j]->y += translate;
			j++;
		}
		i++;
	}
	// }
	// map->max_xval += translate;
	// map->max_yval += translate;
	if (map->min_xval < 0)
	{
		map->max_xval += map->min_xval;
		map->min_xval = 0;
	}
	if (map->min_yval < 0)
	{
		map->max_yval += map->min_yval;
		map->min_yval = 0;
	}
	map->max_xval *= scale;
	map->max_yval *= scale;
}

// void	remap_points_old(t_map *map, int translate, float scale)
// {
// 	int new_x;
// 	int new_y;
// 	// float scale;

// 	// scale = 1;
// 	// scale = 10.0f;
// 	// map->num_cols *= scale;
// 	// map->num_rows *= scale;
// 	while (map->max_xval * scale >= SCREEN_W || map->max_yval * scale >= SCREEN_H)
// 	{
// 		// map->num_cols /= 2;
// 		// map->num_rows /= 2;
// 		scale -= 0.2f;;
// 	}
// 	new_x = map->max_xval * scale;
// 	new_y = map->max_yval * scale;
// 	int in_xrange = map->max_xval - map->min_xval;
// 	int out_xrange = (new_x) - translate;
// 	int in_yrange = map->max_yval - map->min_yval;
// 	int out_yrange = (new_y) - translate;

// 	int i = 0;
// 	int j = 0;
// 	while (i < map->num_rows)
// 	{
// 		j = 0;
// 		while (j < map->num_cols)
// 		{
// 			map->points[i][j]->x = (map->points[i][j]->x - map->min_xval) * out_xrange / in_xrange + translate;
// 			map->points[i][j]->y = (map->points[i][j]->y - map->min_yval) * out_yrange / in_yrange + translate;
// 			j++;
// 		}
// 		i++;
// 	}
// 	map->max_xval = new_x;
// 	map->max_yval = new_y;
// // output = (input - input_start)*output_range / input_range + output_start;
// }

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
			// project_point(points[i][j], i, (map->num_cols - j), map->z_values[i][j], scale, translate);
			project_point(points[i][j],  i, map->num_cols - j, map->z_values[i][j], scale, translate);
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

int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	t_map	*map = read_map(argv[1]);
	int scale = atoi(argv[2]);
	// printf("SEG\n");
	int i = 0;
	int j = 0;
	
	create_points(map, scale, 20);
	mlx_win = mlx_new_window(mlx, SCREEN_W, SCREEN_H, "fdf");
	img.img = mlx_new_image(mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_point ***points = map->points;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (j + 1 < map->num_cols && i != map->num_rows - 1)
				draw_line(&img, points[i][j]->x, points[i][j]->y, points[i][j + 1]->x, points[i][j + 1]->y, 0x00FFFFFF);
			if (i + 1 < map->num_rows && j != 0)
				draw_line(&img, points[i][j]->x, points[i][j]->y, points[i + 1][j]->x, points[i + 1][j]->y, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
