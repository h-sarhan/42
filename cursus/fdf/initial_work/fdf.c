/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/11 14:34:14 by hsarhan          ###   ########.fr       */
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
	int		scale;
	int		i;
	int		num_cols;
	int		j;
	t_point	***points;
	t_point	***points_copy;
	t_point	***proj_pts;

	i = 0;
	scale = 1;
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
	// draw_line(create_point(vars->map->orientation->elms[0][0] * 100, vars->map->orientation->elms[1][0] * 100, vars->map->orientation->elms[2][0] * 100, 0xFF0000),
	// 		create_point(100, 0, 0, 0xFF0000), vars);
	// draw_line(create_point(vars->map->orientation->elms[0][1] * 100, vars->map->orientation->elms[1][1] * 100, vars->map->orientation->elms[2][1] * 100, 0x00FF00),
	// 		create_point(0, 100, 0, 0x00FF00), vars);
	// draw_line(create_point(vars->map->orientation->elms[0][2] * 100, vars->map->orientation->elms[1][2] * 100, vars->map->orientation->elms[2][2] * 100, 0x0000FF),
	// 		create_point(0, 0, 100, 0x0000FF), vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, old_img);
}
