/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:53:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/08 19:29:09 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*create_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		exit_msg("ERROR CREATING MAP\n", EXIT_FAILURE);
	map->num_rows = 0;
	map->num_cols = 0;
	map->points = NULL;
	map->points_copy = NULL;
	map->proj_points = NULL;
	map->rot_x = 0;
	map->rot_y = 0;
	map->rot_z = 0;
	map->min_x = INT_MAX;
	map->max_x = INT_MIN;
	map->min_y = INT_MAX;
	map->max_y = INT_MIN;
	map->max_og_x = INT_MIN;
	map->max_og_y = INT_MIN;
	map->max_og_z = INT_MIN;
	return (map);
}

t_point	*create_point(float x, float y, float z, int color)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	if (point == NULL)
		exit_msg("ERROR CREATING POINT\n", EXIT_FAILURE);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

void	free_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			free(map->proj_points[i][j]);
			free(map->points[i][j]);
			free(map->points_copy[i][j]);
			j++;
		}
		free(map->proj_points[i]);
		free(map->points[i]);
		free(map->points_copy[i]);
		i++;
	}
	free(map->proj_points);
	free(map->points);
	free(map->points_copy);
	free(map);
}
