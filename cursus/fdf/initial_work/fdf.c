/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/12 16:54:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_min_max(t_map *map, t_point ***points)
{
	int	i;
	int	j;
	int	max_xyz[3];

	max_xyz[0] = INT_MIN;
	max_xyz[1] = INT_MIN;
	max_xyz[2] = INT_MIN;
	i = 0;
	while (i < map->num_rows)
	{
		j = -1;
		while (++j < map->num_cols)
		{
			if (points[i][j]->x > max_xyz[0])
				max_xyz[0] = points[i][j]->x;
			if (points[i][j]->y > max_xyz[1])
				max_xyz[1] = points[i][j]->y;
			if (points[i][j]->z > max_xyz[2])
				max_xyz[2] = points[i][j]->z;
		}
		i++;
	}
	map->max_og_x = max_xyz[0];
	map->max_og_y = max_xyz[1];
	map->max_og_z = max_xyz[2];
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
	float		scale;
	int		i;
	int		num_cols;
	int		j;
	t_point	***points;
	t_point	***points_copy;
	t_point	***proj_pts;

	i = 0;
	scale = 1;
	// map = ft_calloc(1, sizeof(t_map));
	map = create_map();
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
	while (scale * num_cols < 400 || scale * num_rows < 300)
		scale += 1;
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
				proj_pts[i][j]->color = 0xFFFFFF;
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
	rotate_points(map);
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
	// x *= vars->scale;
	// y *= vars->scale;
	if (x < 0 || y < 0 || x >= vars->map->win_x || y >= vars->map->win_y)
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
	void	*old_img;

	i = 0;
	j = 0;
	points = vars->map->proj_points;
	old_img = create_new_image(vars);
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
	// find_min_max(vars->map, vars->map->proj_points);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, old_img);
	mlx_string_put(vars->mlx, vars->win, 50, 50, vars->theme,  "[CONTROLS]:");
	mlx_string_put(vars->mlx, vars->win, 70, 70, vars->theme,  "WASD:         Pan");
	mlx_string_put(vars->mlx, vars->win, 70, 90, vars->theme,  "LEFT/RIGHT:   Rotate X");
	mlx_string_put(vars->mlx, vars->win, 70, 110, vars->theme, "UP/DOWN:      Rotate Y");
	mlx_string_put(vars->mlx, vars->win, 70, 130, vars->theme, "Q/E:          Rotate Z");
	mlx_string_put(vars->mlx, vars->win, 70, 150, vars->theme, "+/-:          Zoom In/Out");
	mlx_string_put(vars->mlx, vars->win, 70, 170, vars->theme, "MIDDLE MOUSE: Rotate Freely");
	mlx_string_put(vars->mlx, vars->win, 70, 190, vars->theme, "MOUSE SCROLL: Zoom In/Out");
	mlx_string_put(vars->mlx, vars->win, 70, 210, vars->theme, "C:            Switch Theme");
}
