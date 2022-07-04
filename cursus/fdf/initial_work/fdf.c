/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/04 22:43:27 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotX(t_point *p, float rot)
{
	int	xyz[3];

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = xyz[0];
	p->y = cos(rot) * xyz[1] - sin(rot) * xyz[2];
	p->z = sin(rot) * xyz[1] + cos(rot) * xyz[2];
}

void rotY(t_point *p, float rot)
{
	int	xyz[3];

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = xyz[0] * cos(rot) + sin(rot) * xyz[2];
	p->y = xyz[1];
	p->z = -sin(rot) * xyz[0] + cos(rot) * xyz[2];
}

void rotZ(t_point *p, float rot)
{
	int	xyz[3];

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = xyz[0] * cos(rot) - sin(rot) * xyz[1];
	p->y = xyz[0] * sin(rot) + cos(rot) * xyz[1];
	p->z = xyz[2];
}

void project_point(t_map *map, t_point *projected, t_point *orig, int scale, int translate)
{
	float beta;
	float alpha;

	beta = 45 * (PI / 180.0f);
	alpha = asin(tan(30 * (PI / 180.0f)));
	// projected->x = orig->x - map->max_og_x;
	// projected->y = orig->y - map->max_og_y;
	// projected->z = orig->z - map->max_og_z;
	// find_min_max(map, map->points_copy);
	projected->x = orig->x;
	projected->y = orig->y;
	projected->z = orig->z;
	
	rotZ(projected, beta);
	rotX(projected, alpha + 30 * (PI / 180.0f));
	// projected->x += map->max_og_x;
	// projected->y += map->max_og_y;
	// projected->z = orig->z + map->max_og_z;
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

void	project_points(t_map *map, int scale)
{
	int	i;
	int	j;
	t_point	***projected_points;
	t_point	***points;
	
	points = map->points_copy;
	projected_points = map->projected_points;
	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			project_point(map, projected_points[i][j], points[i][j], scale, 0);
			if (projected_points[i][j]->x < map->min_x)
				map->min_x = projected_points[i][j]->x;
			if (projected_points[i][j]->y < map->min_y)
				map->min_y = projected_points[i][j]->y;
			if (projected_points[i][j]->x > map->max_x)
				map->max_x = projected_points[i][j]->x;
			if (projected_points[i][j]->y > map->max_y)
				map->max_y = projected_points[i][j]->y;
			j++;
		}
		i++;
	}
}

void	rotate_points(t_map *map, int scale, float rot_x, float rot_y)
{
	int	i;
	int	j;
	t_point	***projected_points;
	t_point	***points;
	t_point	***points_copy;

	points = map->points;
	points_copy = map->points_copy;
	projected_points = map->projected_points;
	// find_min_max(map, points);
	printf("ORIGIN IS (%d, %d, %d)\n", map->max_og_x / 2, map->max_og_y / 2, map->max_og_z / 2);
	// my_mlx_pixel_put();
	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			// printf("point is (%d, %d, %d)\n", points_copy[i][j]->x, points_copy[i][j]->y, points_copy[i][j]->z);
			points_copy[i][j]->x = points[i][j]->x;
			points_copy[i][j]->y = points[i][j]->y;
			points_copy[i][j]->z = points[i][j]->z;

			// points_copy[i][j]->x = (map->max_og_x / 2);
			// points_copy[i][j]->y = (map->max_og_y / 2);
			// points_copy[i][j]->z = (map->max_og_z / 2);
 			rotY(points_copy[i][j], rot_y);
			rotX(points_copy[i][j], rot_x);
 			// rotZ(points_copy[i][j], 0);
			// points_copy[i][j]->x += (map->max_og_x / 2);
			// points_copy[i][j]->y += (map->max_og_y / 2);
			// points_copy[i][j]->z += (map->max_og_z / 2);
			// points_copy[i][j]->x += (map->max_og_x / 2);
			// points_copy[i][j]->y += (map->max_og_y / 2);
			// points_copy[i][j]->z += (map->max_og_z / 2);
			// find_min_max(map, points_copy);
			j++;
		}
		i++;
	}
}

void	find_min_max(t_map *map, t_point ***points)
{
	int i = 0;
	int j = 0;
	int max_x = INT_MIN;
	int max_y = INT_MIN;
	int max_z = INT_MIN;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (points[i][j]->x > max_x)
				max_x = points[i][j]->x;
			if (points[i][j]->y > max_y)
				max_y = points[i][j]->y;
			if (points[i][j]->z > max_z)
				max_z = points[i][j]->z;
			j++;
		}
		i++;
	}
	map->max_og_x = max_x;
	map->max_og_y = max_y;
	map->max_og_z = max_z;
}

// TODO: Changes this to use an array to count the number of rows
t_map *read_map(char *map_path, int scale)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	t_map	*map;

	// TODO: Write create map function
	map = ft_calloc(1, sizeof(t_map));
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	// GETTING NUMBER OF COLUMNS, ROWS AND STORING THE LINES
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

	// Get original points
	i = 0;
	int j = 0;
	t_point ***points = ft_calloc(num_rows + 1, sizeof(t_point **));
	t_point ***points_copy = ft_calloc(num_rows + 1, sizeof(t_point **));
	t_point ***projected_points = ft_calloc(num_rows + 1, sizeof(t_point **));
	while (i < num_rows && lines != NULL)
	{
		points[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		points_copy[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		projected_points[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		line = lines->content;
		tokens = ft_split(line, ' ');
		j = 0;
		while (j < num_cols && tokens[j] != NULL)
		{
			projected_points[i][j] = ft_calloc(1, sizeof(t_point));
			points[i][j] = ft_calloc(1, sizeof(t_point));
			points_copy[i][j] = ft_calloc(1, sizeof(t_point));
			if (ft_strchr(tokens[j], ',') != NULL)
				projected_points[i][j]->color = hextoi(ft_strchr(tokens[j], ',') + 1);
			else
				projected_points[i][j]->color = 0x00FFFFFF;
			points[i][j]->x = i * scale;
			points[i][j]->y = (num_cols - j) * scale;
			points[i][j]->z = atoi(tokens[j]) * scale;
			points_copy[i][j]->x = i * scale;
			points_copy[i][j]->y = (num_cols - j) * scale;
			points_copy[i][j]->z = atoi(tokens[j]) * scale;
			j++;
		}
		lines = lines->next;
		free_split_array(tokens);
		i++;
	}
	map->projected_points = projected_points;
	map->points = points;
	map->points_copy = points_copy;
	map->num_cols = j;
	map->num_rows = i;
	project_points(map, scale);
	remap_points(map, 0, 0);
	ft_lstclear(&first, free);
	return (map);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color, t_vars *vars)
{
	char *dst;

	x += vars->translateX;
	y += vars->translateY;
	if (x < 0 || y < 0 || x > vars->win_x || y > vars->win_y)
		return ;
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
			if (map->min_x < 0)
				map->projected_points[i][j]->x -= map->min_x;
			if (map->min_y < 0)
				map->projected_points[i][j]->y -= map->min_y;
			j++;
		}
		i++;
	}
	if (map->min_x < 0)
	{
		map->max_x -= map->min_x;
		map->min_x = 0;
	}
	if (map->min_y < 0)
	{
		map->max_y -= map->min_y;
		map->min_y = 0;
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
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars);
	exit(EXIT_SUCCESS);
	return (0);
}

int handle_keypress(int key_code, void *params)
{
	// ft_putstr_fd("PRINTING KEY CODE ", 1);
	// ft_putnbr_fd(key_code, 1);
	// ft_putendl_fd("", 1);
	t_vars *vars = params;
	if (key_code == KEY_Q || key_code == KEY_ESC || key_code == 113 || key_code == 65307)
	{
		close_window(vars);
	}
	if (key_code == 123)
	{
		// left arrow

		mlx_destroy_image(vars->mlx, vars->img);
		mlx_clear_window(vars->mlx, vars->win);
		vars->map->rot_x--;
		rotate_points(vars->map, vars->scale, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f));
		project_points(vars->map, vars->scale);
		remap_points(vars->map, 0, 0);
		vars->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
		vars->data->img = vars->img;
		vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);
		draw_points(vars);
	}
	if (key_code == 124 || key_code == 65363)
	{
		// right arrow

		mlx_destroy_image(vars->mlx, vars->img);
		mlx_clear_window(vars->mlx, vars->win);
		vars->map->rot_x += 1;
		rotate_points(vars->map, vars->scale, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f));
		project_points(vars->map, vars->scale);
		remap_points(vars->map, 0, 0);
		vars->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
		vars->data->img = vars->img;
		vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);
		draw_points(vars);
	}
	if (key_code == 126)
	{
		// up arrow

		mlx_destroy_image(vars->mlx, vars->img);
		mlx_clear_window(vars->mlx, vars->win);
		// vars->map->rot_y = 10;
		vars->map->rot_y++;
		rotate_points(vars->map, vars->scale, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f));
		project_points(vars->map, vars->scale);
		remap_points(vars->map, 0, 0);
		vars->data->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
		vars->img = vars->data->img;
		vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);
		draw_points(vars);
	}
	if (key_code == 125)
	{
		// down arrow

		mlx_destroy_image(vars->mlx, vars->img);
		mlx_clear_window(vars->mlx, vars->win);
		// vars->map->rot_y = 10;
		vars->map->rot_y--;
		rotate_points(vars->map, vars->scale, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f));
		project_points(vars->map, vars->scale);
		remap_points(vars->map, 0, 0);
		vars->data->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
		vars->img = vars->data->img;
		vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);
		draw_points(vars);
	}
	return (0);
}


#include <time.h>
void	draw_points(t_vars *vars)
{
	// clock_t t = clock();
	int i = 0;
	int j = 0;
	t_point ***points = vars->map->projected_points;
	while (i < vars->map->num_rows)
	{
		j = 0;
		while (j < vars->map->num_cols)
		{
			if (j + 1 < vars->map->num_cols)
				draw_line(vars->data, points[i][j], points[i][j + 1], vars);
			if (i + 1 < vars->map->num_rows)
				draw_line(vars->data, points[i][j], points[i + 1][j], vars);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	// t = clock() - t;
	// double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	// printf("draw_points() took %f seconds to execute \n", time_taken);
}

int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	clock_t t;
	t = clock();
	int scale = atoi(argv[2]);
	t_map *map = read_map(argv[1], scale);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("read_map() took %f seconds to execute \n", time_taken);

	t_data *data;
	data = ft_calloc(1, sizeof(t_data));
	int translateX = map->max_x / 2;
	int translateY = map->max_y / 2;
	mlx_win = mlx_new_window(mlx, map->max_x * 2 + 1 + translateX, map->max_y * 2 + 1 + translateY, "fdf");
	data->img = mlx_new_image(mlx, map->max_x * 2 + 1 + translateX, map->max_y * 2 + 1 + translateY);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	t_vars *vars = ft_calloc(1, sizeof(t_vars));
	vars->mlx = mlx;
	vars->win = mlx_win;
	vars->map = map;
	vars->img = data->img;
	vars->data = data;
	vars->scale = scale;
	vars->win_x = map->max_x * 2 + 1 + translateX;
	vars->win_y = map->max_y * 2 + 1 + translateY;
	vars->translateX = translateX;
	vars->translateY = translateY;
	map->rot_x = 0;
	map->rot_y = 0;
	draw_points(vars);
	mlx_hook(mlx_win, 17, 0, close_window, vars);
	mlx_hook(mlx_win, 2, (1L << 0), handle_keypress, vars);
	mlx_loop(mlx);
	// exit(EXIT_FAILURE);
	// free_map(map);
}
