/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 07:03:55 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/11 07:31:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat3	*x_rotation_matrix(float rot)
{
	t_mat3	*x_rot;
	float	c;
	float	s;

	x_rot = ft_calloc(1, sizeof(t_mat3));
	if (x_rot == NULL)
		return (NULL);
	c = cos(rot);
	s = sin(rot);
	x_rot->elms[0][0] = 1;
	x_rot->elms[0][1] = 0;
	x_rot->elms[0][2] = 0;
	x_rot->elms[1][0] = 0;
	x_rot->elms[1][1] = c;
	x_rot->elms[1][2] = -s;
	x_rot->elms[2][0] = 0;
	x_rot->elms[2][1] = s;
	x_rot->elms[2][2] = c;
	return (x_rot);
}

t_mat3	*y_rotation_matrix(float rot)
{
	t_mat3	*y_rot;
	float	c;
	float	s;

	y_rot = ft_calloc(1, sizeof(t_mat3));
	if (y_rot == NULL)
		return (NULL);
	c = cos(rot);
	s = sin(rot);
	y_rot->elms[0][0] = c;
	y_rot->elms[0][1] = 0;
	y_rot->elms[0][2] = s;
	y_rot->elms[1][0] = 0;
	y_rot->elms[1][1] = 1;
	y_rot->elms[1][2] = 0;
	y_rot->elms[2][0] = -s;
	y_rot->elms[2][1] = 0;
	y_rot->elms[2][2] = c;
	return (y_rot);
}

t_mat3	*z_rotation_matrix(float rot)
{
	t_mat3	*z_rot;
	float	c;
	float	s;

	z_rot = ft_calloc(1, sizeof(t_mat3));
	if (z_rot == NULL)
		return (NULL);
	c = cos(rot);
	s = sin(rot);
	z_rot->elms[0][0] = c;
	z_rot->elms[0][1] = -s;
	z_rot->elms[0][2] = 0;
	z_rot->elms[1][0] = s;
	z_rot->elms[1][1] = c;
	z_rot->elms[1][2] = 0;
	z_rot->elms[2][0] = 0;
	z_rot->elms[2][1] = 0;
	z_rot->elms[2][2] = 1;
	return (z_rot);
}

t_mat3	*mat_mul(t_mat3 *a, t_mat3 *b)
{
	t_mat3	*res;

	res = ft_calloc(1, sizeof(t_mat3));
	if (res == NULL)
		return (NULL);
	res->elms[0][0] = a->elms[0][0] * b->elms[0][0];
	res->elms[0][0] += a->elms[0][1] * b->elms[1][0];
	res->elms[0][0] += a->elms[0][2] * b->elms[2][0];
	res->elms[0][1] = a->elms[0][0] * b->elms[0][1];
	res->elms[0][1] += a->elms[0][1] * b->elms[1][1];
	res->elms[0][1] += a->elms[0][2] * b->elms[2][1];
	res->elms[0][2] = a->elms[0][0] * b->elms[0][2];
	res->elms[0][2] += a->elms[0][1] * b->elms[1][2];
	res->elms[0][2] += a->elms[0][2] * b->elms[2][2];
	res->elms[1][0] = a->elms[1][0] * b->elms[0][0];
	res->elms[1][0] += a->elms[1][1] * b->elms[1][0];
	res->elms[1][0] += a->elms[1][2] * b->elms[2][0];
	res->elms[1][1] = a->elms[1][0] * b->elms[0][1];
	res->elms[1][1] += a->elms[1][1] * b->elms[1][1];
	res->elms[1][1] += a->elms[1][2] * b->elms[2][1];
	res->elms[1][2] = a->elms[1][0] * b->elms[0][2];
	res->elms[1][2] += a->elms[1][1] * b->elms[1][2];
	res->elms[1][2] += a->elms[1][2] * b->elms[2][2];
	res->elms[2][0] = a->elms[2][0] * b->elms[0][0];
	res->elms[2][0] += a->elms[2][1] * b->elms[1][0];
	res->elms[2][0] += a->elms[2][2] * b->elms[2][0];
	res->elms[2][1] = a->elms[2][0] * b->elms[0][1];
	res->elms[2][1] += a->elms[2][1] * b->elms[1][1];
	res->elms[2][1] += a->elms[2][2] * b->elms[2][1];
	res->elms[2][2] = a->elms[2][0] * b->elms[0][2];
	res->elms[2][2] += a->elms[2][1] * b->elms[1][2];
	res->elms[2][2] += a->elms[2][2] * b->elms[2][2];
	free(a);
	free(b);
	return (res);
}

t_point	*mat_point_product(t_mat3 *mat, t_point *p)
{
	t_point	*res;
	float	x;
	float	y;
	float	z;

	x = mat->elms[0][0] * p->x + mat->elms[0][1] * p->y + mat->elms[0][2] * p->z;
	y = mat->elms[1][0] * p->x + mat->elms[1][1] * p->y + mat->elms[1][2] * p->z;
	z = mat->elms[2][0] * p->x + mat->elms[2][1] * p->y + mat->elms[2][2] * p->z;
	res = create_point(x, y, z, p->color);
	free(p);
	return (res);
}