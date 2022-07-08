/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/08 20:48:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_map	*read_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	t_map	*map;
	int		scale;
	int		i;
	int		num_cols;
	int		j;
	t_point	***points;
	t_point	***points_copy;
	t_point	***proj_pts;

	i = 0;
	scale = 1;
	map = ft_calloc(1, sizeof(t_map));
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	tokens = ft_split(line, ' ');
	while (tokens[i] != NULL)
		i++;
	num_cols = i;
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
	while (scale * num_cols < 500 && scale * num_rows < 500)
		scale++;
	i = 0;
	j = 0;
	points = ft_calloc(num_rows + 1, sizeof(t_point **));
	points_copy = ft_calloc(num_rows + 1, sizeof(t_point **));
	proj_pts = ft_calloc(num_rows + 1, sizeof(t_point **));
	while (i < num_rows && lines != NULL)
	{
		points[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		points_copy[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		proj_pts[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		line = lines->content;
		tokens = ft_split(line, ' ');
		j = 0;
		while (j < num_cols && tokens[j] != NULL)
		{
			proj_pts[i][j] = ft_calloc(1, sizeof(t_point));
			points[i][j] = ft_calloc(1, sizeof(t_point));
			points_copy[i][j] = ft_calloc(1, sizeof(t_point));
			if (ft_strchr(tokens[j], ',') != NULL)
				proj_pts[i][j]->color = hextoi(ft_strchr(tokens[j], ',') + 1);
			else
				proj_pts[i][j]->color = 0x00FFFFFF;
			points[i][j]->x = i * scale;
			points[i][j]->y = (num_cols - j) * scale;
			points[i][j]->z = ft_atoi(tokens[j]) * scale;
			points_copy[i][j]->x = i * scale;
			points_copy[i][j]->y = (num_cols - j) * scale;
			points_copy[i][j]->z = ft_atoi(tokens[j]) * scale;
			j++;
		}
		lines = lines->next;
		free_split_array(tokens);
		i++;
	}
	map->proj_points = proj_pts;
	map->points = points;
	map->points_copy = points_copy;
	map->num_cols = j;
	map->num_rows = i;
	find_min_max(map, map->points_copy);
	project_points(map, 1, 'i');
	ft_lstclear(&first, free);
	return (map);
}

void	my_mlx_pixel_put(int x, int y, int color, t_vars *vars)
{
	char	*dst;
	t_data	*data;

	x += vars->translate_x;
	y += vars->translate_y;
	if (x < 0 || y < 0 || x >= vars->win_x || y >= vars->win_y)
		return ;
	data = vars->data;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_points(t_vars *vars)
{
	int		i;
	int		j;
	t_point	***points;
	void	*img_copy;

	i = 0;
	j = 0;
	points = vars->map->proj_points;
	img_copy = vars->img;
	vars->data->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
	vars->img = vars->data->img;
	vars->data->addr = mlx_get_data_addr(vars->data->img,
			&vars->data->bits_per_pixel,
			&vars->data->line_length, &vars->data->endian);
	while (i < vars->map->num_rows)
	{
		j = 0;
		while (j < vars->map->num_cols)
		{
			if (j + 1 < vars->map->num_cols)
				draw_line(points[i][j], points[i][j + 1], vars);
			if (i + 1 < vars->map->num_rows)
				draw_line(points[i][j], points[i + 1][j], vars);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, img_copy);
}

// TODO: CHECK ARGS BEFORE SUBMITTING LIKE AN IDIOT
int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_map	*map;
	t_data	*data;
	t_vars	*vars;

	mlx = mlx_init();
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
	vars = ft_calloc(1, sizeof(t_vars));
	vars->win_x = (abs(map->max_x) + abs(map->min_x)) * 2 + 1;
	vars->win_y = (abs(map->max_y) + abs(map->min_y)) * 2 + 1;
	mlx_win = mlx_new_window(mlx, vars->win_x, vars->win_y, "fdf");
	data = ft_calloc(1, sizeof(t_data));
	data->img = mlx_new_image(mlx, vars->win_x, vars->win_y);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	vars->mlx = mlx;
	vars->win = mlx_win;
	vars->map = map;
	vars->img = data->img;
	vars->data = data;
	vars->scale = 1;
	vars->translate_x = vars->win_x / 2;
	vars->translate_y = vars->win_y / 4;
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
	mlx_hook(mlx_win, 17, 0, close_window, vars);
	mlx_loop_hook(mlx, mouse_rotate, vars);
	draw_points(vars);
	mlx_loop(mlx);
	free(data);
	free_map(map);
	mlx_destroy_image(vars->mlx, vars->img);
	free(mlx);
	free(vars);
}
