/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:21:09 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/11 14:05:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_point(t_point *projected, t_point *orig, char proj)
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
		// rotate_z(projected, beta);
		// rotate_x(projected, alpha + 30 * (PI / 180.0f));
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
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			project_point(projected_points[i][j], points[i][j], proj);
			check_min_max(map, projected_points[i][j]);
			projected_points[i][j]->x *= scale;
			projected_points[i][j]->y *= scale;
			projected_points[i][j]->z *= scale;
			j++;
		}
		i++;
	}
}
