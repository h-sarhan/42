/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:21:09 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/12 17:51:05 by hsarhan          ###   ########.fr       */
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
		beta = 45 * (PI / 180.0f);
		alpha = asin(tan(30 * (PI / 180.0f)));
		projected->x = orig->x;
		projected->y = orig->y;
		projected->z = orig->z;
	}
	else if (proj  == 'p')
	{
		float	zfar = 10;
		float	znear = 0.1;
		float	fov = 1.0f / tan(20 * (PI / 180.0f));
		projected->x = fov * orig->x;
		projected->y = fov * orig->y;
		projected->z = ((-zfar * znear) / (zfar - znear)) * orig->z;
		// if (orig->z != 0)
		// {
		projected->x /= orig->z;
		projected->y /= orig->z;
		// projected->z /= orig->z;
		// }
		// projected->x = (projected->x  + 1) * map->win_x / 4;
		// projected->y = (projected->y  + 1) * map->win_y / 4;
		printf("%f\n", projected->x);
		// printf("Segmentation Fault\n");
		// exit(0);
	}
	// else if (proj == 'o')
	// {
	// 	projected->x = orig->x;
	// 	projected->y = orig->y;
	// }
	// else if (proj == 'c')
	// {
	// 	projected->x = orig->x + 0.5 * orig->z * cos(63.4 * (PI / 180.0f));
	// 	projected->y = orig->y + 0.5 * orig->z * sin(63.4 * (PI / 180.0f));
	// 	projected->z = 0;
	// }
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
	// rotate_points(map);
}
