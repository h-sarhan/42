/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:00:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 20:22:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *read_map_from_ppm(char *map_path)
{
	int		fd;
	char	**tokens;
	t_map	*map;
	int scale = 1;
	map = ft_calloc(1, sizeof(t_map));
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;

	fd = open(map_path, O_RDONLY);
	int w, h;
	char *header = get_next_line(fd);
	if (ft_strncmp(header, "P6\n", ft_strlen(header)) != 0)
	{
		ft_printf("CANT READ THIS LOOL\n");
	}
	header = get_next_line(fd);
	tokens = ft_split(header, ' ');
	w = ft_atoi(tokens[0]);
	h = ft_atoi(tokens[1]);
	
	while (w * scale < 400 && h * scale < 400)
		scale++;
	header = get_next_line(fd);
	t_point ***points = ft_calloc(h + 1, sizeof(t_point **));
	t_point ***points_copy = ft_calloc(h + 1, sizeof(t_point **));
	t_point ***projected_points = ft_calloc(h + 1, sizeof(t_point **));
	for (int i = 0; i < h; i++)
	{
		points[i] = ft_calloc(w + 1, sizeof(t_point *));
		points_copy[i] = ft_calloc(w + 1, sizeof(t_point *));
		projected_points[i] = ft_calloc(w + 1, sizeof(t_point *));
		for (int j = 0; j < w; j++)
		{
			projected_points[i][j] = ft_calloc(1, sizeof(t_point));
			points[i][j] = ft_calloc(1, sizeof(t_point));
			points_copy[i][j] = ft_calloc(1, sizeof(t_point));
			int r, g, b;
			r = 0;
			g = 0;
			b = 0;
			read(fd, &g, 1);
			read(fd, &b, 1);
			read(fd, &r, 1);
			projected_points[i][j]->color = create_trgb(0, r, g, b);
			points[i][j]->x = i;
			points[i][j]->y = (h - j) * scale;
			points[i][j]->z = 0;
			points_copy[i][j]->x = i * scale;
			points_copy[i][j]->y = (h - j) * scale;
			points_copy[i][j]->z = 0;
		}
	}
	map->projected_points = projected_points;
	map->points = points;
	map->points_copy = points_copy;
	map->num_cols = w;
	map->num_rows = h;
	find_min_max(map, map->points_copy);
	project_points(map, scale, 'i');
	return (map);
}
