/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:20:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 00:12:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_map *map, float rot)
{
	t_point	axis;

	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	t_quaternion *q_rot = create_quaternion_rotation(rot * (PI / 180.0f), &axis);
	map->orientation = rotate_quaternion(q_rot, map->orientation);
}

void	rotate_y(t_map *map, float rot)
{
	t_point	axis;

	axis.x = 0;
	axis.y = -1;
	axis.z = 0;
	t_quaternion *q_rot = create_quaternion_rotation(rot * (PI / 180.0f), &axis);
	map->orientation = rotate_quaternion(q_rot, map->orientation);
}

void	rotate_z(t_map *map, float rot)
{
	t_point	axis;

	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	t_quaternion *q_rot = create_quaternion_rotation(rot * (PI / 180.0f), &axis);
	map->orientation = rotate_quaternion(q_rot, map->orientation);
}


void	rotate_x_matrix(t_point *p, float rot)
{
	int	xyz[3];

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = xyz[0];
	p->y = cos(rot) * xyz[1] - sin(rot) * xyz[2];
	p->z = sin(rot) * xyz[1] + cos(rot) * xyz[2];
}

void	rotate_y_matrix(t_point *p, float rot)
{
	int	xyz[3];

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = xyz[0] * cos(rot) + sin(rot) * xyz[2];
	p->y = xyz[1];
	p->z = -sin(rot) * xyz[0] + cos(rot) * xyz[2];
}

void	rotate_z_matrix(t_point *p, float rot)
{
	int	xyz[3];

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = xyz[0] * cos(rot) - sin(rot) * xyz[1];
	p->y = xyz[0] * sin(rot) + cos(rot) * xyz[1];
	p->z = xyz[2];
}

void	rotate_points(t_map *map, t_vars *vars)
{
	int		i;
	int		j;
	t_point	***points;
	t_point	***points_copy;

	points = map->points;
	points_copy = map->points_copy;
	i = 0;
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->min_z = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	map->max_z = INT_MIN;
	while (i < map->num_rows)
	{
		j = -1;
		while (++j < map->num_cols)
		{
			points_copy[i][j]->x = points[i][j]->x - (map->max_og_x / 2.0f);
			points_copy[i][j]->y = points[i][j]->y - (map->max_og_y / 2.0f);
			points_copy[i][j]->z = points[i][j]->z - (map->max_og_z / 2.0f);
			rotate_point(map->orientation, points_copy[i][j]);
			// if (map->vars)
			// if ((map->max_z -  points_copy[i][j]->z) != 0)
			// {
			// points_copy[i][j]->z /= orig->z;
			// }

			if (vars->proj == 'p')
			{
				points_copy[i][j]->x /= (map->max_og_z - points_copy[i][j]->z)  * 0.005;
				points_copy[i][j]->y /= (map->max_og_z -  points_copy[i][j]->z) * 0.005;
				points_copy[i][j]->x = (points_copy[i][j]->x + 2000 / 2) / 2000;
				points_copy[i][j]->y = (points_copy[i][j]->y + 2000 / 2) / 2000;
				points_copy[i][j]->x *= map->win_x;
				points_copy[i][j]->y *= map->win_y;
			}
			else
			{
				points_copy[i][j]->x += (map->max_og_x / 2.0f) + map->win_x / 4;
				points_copy[i][j]->y += (map->max_og_y / 2.0f) + map->win_y / 4;
				points_copy[i][j]->z += (map->max_og_z / 2.0f);
			}
			check_min_max(map, points_copy[i][j]);
		}
		i++;
	}
}
