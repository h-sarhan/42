/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 21:20:50 by hsarhan          ###   ########.fr       */
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

void project_point(t_point *projected, t_point *orig, char proj)
{
	float	beta;
	float	alpha;

	if (proj == 'i')
	{
		beta = 45 * (PI / 180.0f);
		alpha = asin(tan(30 * (PI / 180.0f)));
		projected->x = orig->x;
		projected->y = orig->y;
		projected->z = orig->z;

		rotZ(projected, beta);
		rotX(projected, alpha + 30 * (PI / 180.0f));
	}
	else if (proj == 'o')
	{
		projected->x = orig->x;
		projected->y = orig->y;
	}
	else if (proj == 'c')
	{
		projected->x = orig->x + 0.5 * orig->z * cos(63.4 * (PI / 180.0f));
		projected->y = orig->y + 0.5 * orig->z * sin(63.4 * (PI / 180.0f));
		projected->z = 0;
	}
}


void free_split_array(char **arr)
{
	int	i;

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

void	project_points(t_map *map, float scale, char proj)
{
	int		i;
	int		j;
	t_point	***projected_points;
	t_point	***points;

	points = map->points_copy;
	projected_points = map->proj_points;
	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			project_point(projected_points[i][j], points[i][j], proj);
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
}

void	rotate_points(t_map *map, float rot_x, float rot_y, float rot_z)
{
	int		i;
	int		j;
	t_point	***projected_points;
	t_point	***points;
	t_point	***points_copy;

	points = map->points;
	points_copy = map->points_copy;
	projected_points = map->proj_points;
	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
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
			j++;
		}
		i++;
	}
}

void	find_min_max(t_map *map, t_point ***points)
{
	int	i;
	int	j;
	int	max_x;
	int	max_y;
	int	max_z;

	max_x = INT_MIN;
	max_y = INT_MIN;
	max_z = INT_MIN;
	i = 0;
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

t_map *read_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	t_map	*map;
	int		scale = 1;

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
	map->proj_points = projected_points;
	map->points = points;
	map->points_copy = points_copy;
	map->num_cols = j;
	map->num_rows = i;
	find_min_max(map, map->points_copy);
	project_points(map, 1, 'i');
	ft_lstclear(&first, free);
	return (map);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color, t_vars *vars)
{
	char *dst;

	x += vars->translateX;
	y += vars->translateY;
	if (x < 0 || y < 0 || x >= vars->win_x || y >= vars->win_y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void free_map(t_map *map)
{
	int	i;
	int	j = 0;

	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			free(map->proj_points[i][j]);
			free(map->points[i][j]);
			j++;
		}
		free(map->proj_points[i]);
		free(map->points[i]);
		i++;
	}
	free(map->proj_points);
	free(map->points);
	free(map);
}

int	close_window(void *params)
{
	t_vars *vars = params;
	ft_putendl_fd("QUITTING PROGRAM!", 1);
	free_map(vars->map);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img);
	free(vars);
	exit(EXIT_SUCCESS);
	return (0);
}


int	handle_keypress(int key_code, void *params)
{
	// ft_putstr_fd("PRINTING KEY CODE ", 1);
	// ft_putnbr_fd(key_code, 1);
	// ft_putendl_fd("", 1);
	t_vars *vars = params;
	if (key_code == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
	if (key_code == 13)
	{
		// w
		vars->translateY -= 10;
	}
	if (key_code == 0)
	{
		// a
		vars->translateX -= 10;
	}
	if (key_code == 1)
	{
		// s
		vars->translateY += 10;
	}
	if (key_code == 2)
	{
		// d
		vars->translateX += 10;
	}
	if (key_code == 123 && vars->proj != 'o')
	{
		// left arrow
		vars->map->rot_x -= 3;
	}
	if (key_code == 124 && vars->proj != 'o')
	{
		// right arrow
		vars->map->rot_x += 3;
	}
	if (key_code == 126 && vars->proj != 'o')
	{
		// up arrow
		vars->map->rot_y += 3;
	}
	if (key_code == 125 && vars->proj != 'o')
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
	if (key_code == 35)
	{
		// p
		if (vars->proj == 'i')
		{
			vars->proj = 'o';
			vars->map->rot_x = 0;
			vars->map->rot_y = 0;
			vars->map->rot_z = 90;
		}
		else if (vars->proj == 'o')
		{
			vars->proj = 'c';
			vars->map->rot_x = 0;
			vars->map->rot_y = 0;
			vars->map->rot_z = 0;
		}
		else if (vars->proj == 'c')
		{
			vars->proj = 'i';
			vars->map->rot_x = 0;
			vars->map->rot_y = 0;
			vars->map->rot_z = 0;
		}
	}
	rotate_points(vars->map, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f), vars->map->rot_z * (PI/ 180.0f));
	project_points(vars->map, vars->scale, vars->proj);
	draw_points(vars);
	return (0);
}



#include <time.h>
void	draw_points(t_vars *vars)
{
	int i = 0;
	int j = 0;
	t_point ***points = vars->map->proj_points;
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
}

int	handle_mouse_down(int key_code, int x, int y, void *params)
{
	(void)x;
	(void)y;
	if (key_code == 3)
	{
		t_vars *vars = params;
		vars->m_down = 1;
	}
	return (0);
}

int	handle_mouse_up(int key_code, int x, int y, void *params)
{
	(void)x;
	(void)y;
	if (key_code == 3)
	{
		t_vars *vars = params;
		vars->m_down = 0;
	}
	return (0);
}

int	mouse_rotate(void *params)
{
	t_vars	*vars = params;
	if (vars->m_down == 1)
	{
		vars->m_prev_x = vars->m_x;
		vars->m_prev_y = vars->m_y;
		mlx_mouse_get_pos(vars->win, &vars->m_x, &vars->m_y);
		if (vars->m_prev_x < vars->m_x)
			vars->map->rot_x += 2;
		else if (vars->m_prev_x > vars->m_x)
			vars->map->rot_x -= 2;
		if (vars->m_prev_y < vars->m_y)
			vars->map->rot_y += 2;
		else if (vars->m_prev_y > vars->m_y)
			vars->map->rot_y -= 2;
		rotate_points(vars->map, vars->map->rot_x * (PI / 180.0f), vars->map->rot_y * (PI / 180.0f), vars->map->rot_z * (PI / 180.0f));
		project_points(vars->map, vars->scale, vars->proj);
		draw_points(vars);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	t_map *map;
	if (argc != 2)
	{
		ft_printf("WRONG NUMBER OF ARGUMENTS!!!!!!!!!!!!!!!!!!!!!!\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strnstr(argv[1], ".ppm", ft_strlen(argv[1])) != NULL
		|| ft_strnstr(argv[1], ".PPM", ft_strlen(argv[1])) != NULL)
		map = read_map_from_ppm(argv[1]);
	else
		map = read_map(argv[1]);
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;

	t_data *data;
	data = ft_calloc(1, sizeof(t_data));
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
	vars->proj = 'i';
	vars->done = 0;
	mlx_hook(mlx_win, 2, (1L << 0), handle_keypress, vars);
	mlx_hook(mlx_win, 4, 0, handle_mouse_down, vars);
	mlx_hook(mlx_win, 5, 0, handle_mouse_up, vars);
	mlx_loop_hook(mlx, mouse_rotate, vars);
	mlx_hook(mlx_win, 17, 0, close_window, vars);
	draw_points(vars);
	mlx_loop(mlx);
}
