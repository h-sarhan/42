/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 15:04:32 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <time.h>
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
	// find_min_max(map, map->points_copy);
	projected->x = orig->x;
	projected->y = orig->y;
	projected->z = orig->z;
	
	rotZ(projected, beta);
	rotX(projected, alpha + 30 * (PI / 180.0f));
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

void	project_points(t_map *map, float scale)
{
	int	i;
	int	j;
	t_point	***projected_points;
	t_point	***points;
	clock_t t;
	t = clock();
	points = map->points_copy;
	projected_points = map->projected_points;
	// find_min_max(map, map->points_copy);
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
			projected_points[i][j]->x *= scale;
			projected_points[i][j]->y *= scale;
			projected_points[i][j]->z *= scale;
			j++;
		}
		i++;
	}
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("project_points() took %f seconds to execute \n", time_taken);
}

void	rotate_points(t_map *map, int scale, float rot_x, float rot_y, float rot_z)
{
	int	i;
	int	j;
	t_point	***projected_points;
	t_point	***points;
	t_point	***points_copy;
	clock_t t;
	t = clock();
	// t_map *map = read_map(argv[1], scale);
	points = map->points;
	points_copy = map->points_copy;
	projected_points = map->projected_points;
	// find_min_max(map, points);
	// printf("ORIGIN IS (%d, %d, %d)\n", map->max_og_x / 2, map->max_og_y / 2, map->max_og_z / 2);
	// my_mlx_pixel_put();
	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			// find_min_max(map, points);
			// printf("point is (%d, %d, %d)\n", points_copy[i][j]->x, points_copy[i][j]->y, points_copy[i][j]->z);
			points_copy[i][j]->x = points[i][j]->x;
			points_copy[i][j]->y = points[i][j]->y;
			points_copy[i][j]->z = points[i][j]->z;
			points_copy[i][j]->x -= (map->max_og_x / 2);
			points_copy[i][j]->y -= (map->max_og_y / 2);
			points_copy[i][j]->z -= (map->max_og_z / 2);
			rotX(points_copy[i][j], rot_x);
 			rotY(points_copy[i][j], rot_y);
 			rotZ(points_copy[i][j], rot_z);
			points_copy[i][j]->x += (map->max_og_x / 2);
			points_copy[i][j]->y += (map->max_og_y / 2);
			points_copy[i][j]->z += (map->max_og_z / 2);
			// points_copy[i][j]->x *= scale;
			// points_copy[i][j]->y *= scale;
			// points_copy[i][j]->z *= scale;
			
			j++;
		}
		i++;
	}
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("rotate_points() took %f seconds to execute \n", time_taken);
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
t_map *read_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	t_map	*map;
	int scale = 1;

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
	first = lines;
	num_rows = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		num_rows++;
		line = get_next_line(fd);
	}

	while (scale * num_cols < 500 && scale * num_rows < 500)
		scale++;
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
	find_min_max(map, map->points_copy);
	project_points(map, 1);
	// remap_points(map, 0, 0);
	ft_lstclear(&first, free);
	return (map);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color, t_vars *vars)
{
	char *dst;

	x += vars->translateX;
	y += vars->translateY;
	// x *= vars->scale;
	// y *= vars->scale;
	if (x < 0 || y < 0 || x >= vars->win_x || y >= vars->win_y)
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
	ft_putstr_fd("PRINTING KEY CODE ", 1);
	ft_putnbr_fd(key_code, 1);
	ft_putendl_fd("", 1);
	t_vars *vars = params;
	if (key_code == KEY_ESC)
		close_window(vars);
	if (key_code == 13)
	{
		// w
		vars->translateY -= 5;
	}
	if (key_code == 0)
	{
		// a
		vars->translateX -= 5;
	}
	if (key_code == 1)
	{
		// s
		vars->translateY += 5;
	}
	if (key_code == 2)
	{
		// d
		vars->translateX += 5;
	}
	if (key_code == 123 || key_code == 65361)
	{
		// left arrow
		vars->map->rot_x -= 3;
	}
	if (key_code == 124 || key_code == 65363)
	{
		// right arrow
		vars->map->rot_x += 3;
	}
	if (key_code == 126 || key_code == 65362)
	{
		// up arrow
		vars->map->rot_y += 3;
	}
	if (key_code == 125 || key_code == 65364)
	{
		// down arrow
		vars->map->rot_y -= 3;
	}
	if (key_code == 12)
	{
		// z key
		vars->map->rot_z += 3;
	}
	if (key_code == 14)
	{
		// x key
		vars->map->rot_z -= 3;
	}
	if (key_code == 24)
	{
		// +
		vars->scale += 0.1;
	}
	if (key_code == 27)
	{
		// +
		vars->scale -= 0.1;
	}
	// scale_points(vars);
	rotate_points(vars->map, vars->scale, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f), vars->map->rot_z * (PI/ 180.0f));
	project_points(vars->map, vars->scale);
	draw_points(vars);
	return (0);
}



#include <time.h>
void	draw_points(t_vars *vars)
{
	clock_t t = clock();
	int i = 0;
	int j = 0;
	t_point ***points = vars->map->projected_points;
	void *img_copy = vars->img;
	vars->data->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
	vars->img = vars->data->img;
	vars->data->addr = mlx_get_data_addr(vars->data->img, &vars->data->bits_per_pixel, &vars->data->line_length, &vars->data->endian);
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
	// TODO: MOVE THIS ABOVE THE WHILE LOOP
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, img_copy);
	// mlx_clear_window(vars->mlx, vars->win);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("draw_points() took %f seconds to execute \n", time_taken);
}

int handle_mouse_down(int key_code, int x, int y, void *params)
{
	(void)x;
	(void)y;
	if (key_code == 3)
	{
		t_vars *vars = params;
		vars->m_down = 1;
	}
	
}
int handle_mouse_up(int key_code, int x, int y, void *params)
{
	(void)x;
	(void)y;
	if (key_code == 3)
	{
		t_vars *vars = params;
		vars->m_down = 0;
	}
	
}

int	mouse_rotate(void *params)
{
	t_vars	*vars = params;
	// vars->m_x = x;
	// vars->m_y = y;
	if (vars->m_down == 1)
	{
		vars->m_prev_x = vars->m_x;
		vars->m_prev_y = vars->m_y;
		mlx_mouse_get_pos(vars->win, &vars->m_x, &vars->m_y);
		// mlx_mouse_get_pos(vars->mlx, vars->win, &vars->m_x, &vars->m_y);
		printf("MOUSE AT POS (%d, %d)\n", vars->m_x, vars->m_y);
		if (vars->m_prev_x < vars->m_x)
			vars->map->rot_x += 2;
		else if (vars->m_prev_x > vars->m_x)
			vars->map->rot_x -= 2;
		if (vars->m_prev_y < vars->m_y)
			vars->map->rot_y += 2;
		else if (vars->m_prev_y > vars->m_y)
			vars->map->rot_y -= 2;
		rotate_points(vars->map, vars->scale, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f), vars->map->rot_z * (PI / 180.0f));
		project_points(vars->map, vars->scale);
		// scale_points(vars);
		draw_points(vars);
	}
}
	

int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	// int scale = 5;
	// printf("SEG\n");
	clock_t t;
	t = clock();
	// t_map *map = read_map(argv[1], scale);
	t_map *map;
	if (ft_strnstr(argv[1], ".ppm", ft_strlen(argv[1])) != NULL)
		map = read_map_from_ppm(argv[1]);
	else
		map = read_map(argv[1]);
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("read_map() took %f seconds to execute \n", time_taken);

	t_data *data;
	data = ft_calloc(1, sizeof(t_data));
	int translateX = 0;
	int translateY = 0;
	t_vars *vars = ft_calloc(1, sizeof(t_vars));
	vars->win_x = (abs(map->max_x) + abs(map->min_x)) * 2 + 1;
	vars->win_y = (abs(map->max_y) + abs(map->min_y)) * 2 + 1;
	mlx_win = mlx_new_window(mlx,vars->win_x, vars->win_y, "fdf");
	data->img = mlx_new_image(mlx, vars->win_x, vars->win_y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	vars->mlx = mlx;
	vars->win = mlx_win;
	vars->map = map;
	vars->img = data->img;
	vars->data = data;
	vars->scale = 1;
	vars->translateX = vars->win_x / 2;
	vars->translateY = vars->win_y / 4;
	vars->drawing_frame = 0;
	vars->m_prev_x = -1;
	vars->m_prev_y = -1;
	vars->m_x = -1;
	vars->m_y = -1;
	vars->m_down = 0;
	vars->pan_x = 0;
	vars->pan_y = 0;
	mlx_hook(mlx_win, 17, 0, close_window, vars);
	mlx_hook(mlx_win, 2, (1L << 0), handle_keypress, vars);
	mlx_hook(mlx_win, 4, 0, handle_mouse_down, vars);
	mlx_hook(mlx_win, 5, 0, handle_mouse_up, vars);
	mlx_loop_hook(mlx, mouse_rotate, vars);
	draw_points(vars);
	// mlx_mouse_hook(vars->win, handle_mouse, &vars);
	mlx_loop(mlx);
	// exit(EXIT_FAILURE);
	// free_map(map);
}
