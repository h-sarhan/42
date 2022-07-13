/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:21:09 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 15:21:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO: THIS FUNCTION IS USELESS NOW
void	project_point(t_map *map, t_point *projected, t_point *orig, char proj)
{
	float	beta;
	float	alpha;

	if (proj == 'i')
	{
		projected->x = orig->x;
		projected->y = orig->y;
	}
	else if (proj == 'c')
	{
		projected->x = orig->x + 0.5 * orig->z * cos(63.4 * (PI / 180.0f));
		projected->y = orig->y + -0.5 * orig->z * sin(63.4 * (PI / 180.0f));
		projected->z = 0;
	}
}

void	check_min_max(t_map *map, t_point *point)
{
	if (point->x < map->min_x)
		map->min_x = point->x;
	if (point->y < map->min_y)
		map->min_y = point->y;
	if (point->x > map->max_x)
		map->max_x = point->x;
	if (point->y > map->max_y)
		map->max_y = point->y;
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
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			project_point(map, projected_points[i][j], points[i][j], proj);
			projected_points[i][j]->x -= (map->max_og_x / 2.0f);
			projected_points[i][j]->y -= (map->max_og_y / 2.0f);
			projected_points[i][j]->z -= (map->max_og_z / 2.0f);
			projected_points[i][j]->x *= scale;
			projected_points[i][j]->y *= scale;
			projected_points[i][j]->z *= scale;
			projected_points[i][j]->x += (map->max_og_x / 2.0f);
			projected_points[i][j]->y += (map->max_og_y / 2.0f);
			projected_points[i][j]->z += (map->max_og_z / 2.0f);
			check_min_max(map, projected_points[i][j]);
			j++;
		}
		i++;
	}
}
