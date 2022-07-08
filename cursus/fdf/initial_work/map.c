/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:53:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/08 17:23:54 by hsarhan          ###   ########.fr       */
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
	map->rot_acc = ft_calloc(3, sizeof(t_vector *));
	if (map->rot_acc == NULL)
	{
		printf("HUH\n");
	}
	map->rot_acc[0] = ft_calloc(1, sizeof(t_vector));
	map->rot_acc[1] = ft_calloc(1, sizeof(t_vector));
	map->rot_acc[2] = ft_calloc(1, sizeof(t_vector));
	map->rot_acc[0]->x = 1;
	map->rot_acc[0]->y = 0;
	map->rot_acc[0]->z = 0;
	map->rot_acc[0]->color = 0;
	map->rot_acc[1]->x = 0;
	map->rot_acc[1]->y = 1;
	map->rot_acc[1]->z = 0;
	map->rot_acc[1]->color = 0;
	map->rot_acc[2]->x = 0;
	map->rot_acc[2]->y = 0;
	map->rot_acc[2]->z = 1;
	map->rot_acc[2]->color = 0;
	return (map);
}

t_vector	*create_point(float x, float y, float z, int color)
{
	t_vector	*point;

	point = ft_calloc(1, sizeof(t_vector));
	if (point == NULL)
		exit_msg("ERROR CREATING POINT\n", EXIT_FAILURE);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

void	multiply_rot_matrix(t_vector **rot_acc, t_vector *ax, float rot)
{
	t_vector	m1[3];
	t_vector	m2[3];
	float		cos_rot;
	float		sin_rot;
	float		m_cos_rot;
	// float		xyz[3];


	m1[0].x = rot_acc[0]->x;
	m1[0].y = rot_acc[0]->y;
	m1[0].z = rot_acc[0]->z;
	m1[1].x = rot_acc[1]->x;
	m1[1].y = rot_acc[1]->y;
	m1[1].z = rot_acc[1]->z;
	m1[2].x = rot_acc[2]->x;
	m1[2].y = rot_acc[2]->y;
	m1[2].z = rot_acc[2]->z;
	// xyz[0] = p->x;
	// xyz[1] = p->y;
	// xyz[2] = p->z;
	cos_rot = cos(rot);
	sin_rot = sin(rot);
	m_cos_rot = 1 - cos_rot;
	m2[0].x = cos_rot + ax->x * ax->x * m_cos_rot;
	m2[0].y = ax->x * ax->y * m_cos_rot - ax->z * sin_rot;
	m2[0].z = ax->x * ax->z * m_cos_rot + ax->y * sin_rot;
	m2[1].x = ax->y * ax->x * m_cos_rot + ax->z * sin_rot;
	m2[1].y = cos_rot + ax->y * ax->y * m_cos_rot;
	m2[1].z = ax->y * ax->z * m_cos_rot - ax->x * sin_rot;
	m2[2].x = ax->z * ax->x * m_cos_rot - ax->y * sin_rot;
	m2[2].y = ax->z * ax->y * m_cos_rot + ax->x * sin_rot;
	m2[2].z = cos_rot + ax->z * ax->z * m_cos_rot;
	rot_acc[0]->x = (m1[0].x * m2[0].x + m1[0].y * m2[1].x + m1[0].z * m2[2].x);
	rot_acc[0]->y = (m1[0].x * m2[0].y + m1[0].y * m2[1].y + m1[0].z * m2[2].y);
	rot_acc[0]->z = (m1[0].x * m2[0].z + m1[0].y * m2[1].z + m1[0].z * m2[2].z);
	rot_acc[1]->x = (m1[1].x * m2[0].x + m1[1].y * m2[1].x + m1[1].z * m2[2].x);
	rot_acc[1]->y = (m1[1].x * m2[0].y + m1[1].y * m2[1].y + m1[1].z * m2[2].y);
	rot_acc[1]->z = (m1[1].x * m2[0].z + m1[1].y * m2[1].z + m1[1].z * m2[2].z);
	rot_acc[2]->x = (m1[2].x * m2[0].x + m1[2].y * m2[1].x + m1[2].z * m2[2].x);
	rot_acc[2]->y = (m1[2].x * m2[0].y + m1[2].y * m2[1].y + m1[2].z * m2[2].y);
	rot_acc[2]->z = (m1[2].x * m2[0].z + m1[2].y * m2[1].z + m1[2].z * m2[2].z);
}
