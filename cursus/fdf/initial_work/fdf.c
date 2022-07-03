/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/02 18:56:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotX(t_point *p, float x, float y, float z, float rot)
{
	p->x = x;
	p->y = cos(rot) * y - sin(rot) * z;
	p->z = -sin(rot) * y + cos(rot) * z;
}

void rotY(t_point *p, float x, float y, float z, float rot)
{
	p->x = x * cos(rot) + sin(cos(rot)) * z;
	p->y = y;
	p->z = -sin(rot) * x + cos(rot) * z;
}

void rotZ(t_point *p, float x, float y, float z, float rot)
{
	p->x = x * cos(rot) - sin(cos(rot)) * y;
	p->y = x * sin(rot) + cos(rot) * y;
	p->z = z;
}

void project_point(t_point *p, int x, int y, int z, int scale, int translate)
{
	float beta;
	float alpha;

	beta = 45 * (PI / 180.0f);
	alpha = asin(tan(30 * (PI / 180.0f)));
	p->x = x * scale;
	p->y = y * scale;
	p->z = z * scale;
	rotZ(p, p->x, p->y, p->z, beta);
	rotX(p, p->x, p->y, p->z, alpha + 30 * (PI / 180.0f));
}

void free_split_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_lines(void *split_array)
{
	free_split_array(split_array);
}

t_map *read_map(char *map_path, int scale)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->min_xval = INT_MAX;
	map->min_yval = INT_MAX;
	map->max_xval = INT_MIN;
	map->max_yval = INT_MIN;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	tokens = ft_split(line, ' ');
	int i = 0;
	while (tokens[i] != NULL)
		i++;
	int num_cols = i;
	free_split_array(tokens);
	lines = NULL;
	num_rows = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		num_rows++;
		line = get_next_line(fd);
	}
	first = lines;
	i = 0;
	int j = 0;
	t_point ***projected_points = ft_calloc(num_rows + 1, sizeof(t_point **));
	t_point ***points = ft_calloc(num_rows + 1, sizeof(t_point **));
	while (i < num_rows && lines != NULL)
	{
		projected_points[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		points[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		line = lines->content;
		tokens = ft_split(line, ' ');
		j = 0;
		while (j < num_cols && tokens[j] != NULL)
		{
			projected_points[i][j] = ft_calloc(1, sizeof(t_point));
			points[i][j] = ft_calloc(1, sizeof(t_point));
			if (ft_strchr(tokens[j], ',') != NULL)
				projected_points[i][j]->color = hextoi(ft_strchr(tokens[j], ',') + 1);
			else
				projected_points[i][j]->color = 0x00FFFFFF;

			points[i][j]->x = i;
			points[i][j]->y = num_cols - j;
			points[i][j]->z = atoi(tokens[j]);
			project_point(projected_points[i][j], i, num_cols - j, atoi(tokens[j]), scale, 0);
			if (projected_points[i][j]->x < map->min_xval)
				map->min_xval = projected_points[i][j]->x;
			if (projected_points[i][j]->y < map->min_yval)
				map->min_yval = projected_points[i][j]->y;
			if (projected_points[i][j]->x > map->max_xval)
				map->max_xval = projected_points[i][j]->x;
			if (projected_points[i][j]->y > map->max_yval)
				map->max_yval = projected_points[i][j]->y;
			j++;
		}
		lines = lines->next;
		free_split_array(tokens);
		i++;
	}
	map->projected_points = projected_points;
	map->points = points;
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	remap_points(map, 0, 0);
	ft_lstclear(&first, free);
	return (map);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void remap_points(t_map *map, int new_x, int new_y)
{
	int i = 0;
	int j = 0;

	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->min_xval < 0)
				map->projected_points[i][j]->x -= map->min_xval;
			if (map->min_yval < 0)
				map->projected_points[i][j]->y -= map->min_yval;
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

void free_map(t_map *map)
{
	int i = 0;
	i = 0;
	int j = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			free(map->projected_points[i][j]);
			free(map->points[i][j]);
			j++;
		}
		free(map->projected_points[i]);
		free(map->points[i]);
		i++;
	}
	free(map->projected_points);
	free(map->points);
	free(map);
}

int close_window(void *params)
{
	t_vars *vars = params;
	ft_putendl_fd("QUITTING PROGRAM!", 1);
	free_map(vars->map);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img);
	free(vars);
	exit(EXIT_SUCCESS);
	return (0);
}

int handle_keypress(int key_code, void *params)
{
	ft_putstr_fd("PRINTING KEY CODE ", 1);
	ft_putnbr_fd(key_code, 1);
	ft_putendl_fd("", 1);
	t_vars *vars = params;
	if (key_code == KEY_Q || key_code == KEY_ESC || key_code == 113 || key_code == 65307)
	{
		close_window(vars);
	}
	// if (key_code == 124 || key_code == 65363)
	// {
	// 	// right arrow
	// 	int i = 0;
	// 	int j = 0;
	// 	t_point	***points = vars->map->points;
	// 	t_point	***projected_points = vars->map->projected_points;
	// 	while (points[i] != NULL)
	// 	{
	// 		j = 0;
	// 		while (points[i][j] != NULL)
	// 		{
	// 			rotZ(points[i][j], points[i][j]->x, points[i][j]->y, points[i][j]->z, 10);
	// 			// project_point(projected_points[i][j], points[])
	// 			j++;
	// 		}
	// 	}
		
	// 	// rotZ();
	// }
	return (0);
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
	int scale = atoi(argv[2]);
	t_map *map = read_map(argv[1], scale);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("read_map() took %f seconds to execute \n", time_taken);

	int i = 0;
	int j = 0;

	int translate = 20;
	mlx_win = mlx_new_window(mlx, map->max_xval + translate + 1, map->max_yval + translate + 1, "fdf");
	img.img = mlx_new_image(mlx, map->max_xval + translate + 1, map->max_yval + translate + 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t_vars *vars = ft_calloc(1, sizeof(t_vars));
	vars->mlx = mlx;
	vars->win = mlx_win;
	vars->map = map;
	vars->img = img.img;
	t = clock();
	t_point ***points = map->projected_points;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (j + 1 < map->num_cols)
				draw_line(&img, points[i][j], points[i][j + 1]);
			if (i + 1 < map->num_rows)
				draw_line(&img, points[i][j], points[i + 1][j]);
			j++;
		}
		i++;
	}
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("draw_points() took %f seconds to execute \n", time_taken);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 17, 0, close_window, vars);
	mlx_hook(mlx_win, 2, (1L << 0), handle_keypress, vars);
	mlx_loop(mlx);
	exit(EXIT_FAILURE);
	// free_map(map);
}
