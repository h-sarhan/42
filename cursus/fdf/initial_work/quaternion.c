/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:08:02 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/09 14:28:09 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quaternion	*create_quaternion(float x, float y, float z, float w)
{
	t_quaternion	*q;

	q = ft_calloc(1, sizeof(t_quaternion));
	if (q == NULL)
		return (NULL);
	q->x = x;
	q->y = y;
	q->z = z;
	q->w = w;
	return (q);
}

// Use like this
// orientation = Compose(rotationChange, orientation);
t_quaternion	*rotate_quaternion(t_quaternion *rot, t_quaternion *q)
{
	t_quaternion	*q_new;
	float			x;
	float			y;
	float			z;
	float			w;

	if (rot == NULL)
		printf("ROT IS NULL\n");
	if (q == NULL)
		printf("Q IS NULL\n");
	x = rot->w * q->x + rot->x * q->w + rot->y * q->z - rot->z * q->y;
	y = rot->w * q->y - rot->x * q->z + rot->y * q->w + rot->z * q->x;
	z = rot->w * q->z + rot->x * q->y - rot->y * q->x + rot->z * q->w;
	w = rot->w * q->w - rot->x * q->x - rot->y * q->y - rot->z * q->z;
	q_new = create_quaternion(x, y, z, w);
	free(rot);
	free(q);
	return (q_new);
}

t_quaternion	*create_quaternion_rotation(float rot, t_point *axis)
{
	t_quaternion	*q;
	float			s;

	s = sin(rot / 2.0f);
	q = create_quaternion(axis->x * s, axis->y * s, axis->z * s, cos(rot/ 2.0f));
	if (q == NULL)
		return (NULL);
	return (q);
}

void	rotate_point(t_quaternion *q, t_point *p)
{
	float x = q->x * 2.0f;
	float y = q->y * 2.0f;
	float z = q->z * 2.0f;
	float xx = q->x * x;
	float yy = q->y * y;
	float zz = q->z * z;
	float xy = q->x * y;
	float xz = q->x * z;
	float yz = q->y * z;
	float wx = q->w * x;
	float wy = q->w * y;
	float wz = q->w * z;
	
	float	xyz[3];
	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	p->x = (1.0f - (yy + zz)) * xyz[0] + (xy - wz) * xyz[1] + (xz + wy) * xyz[2];
	p->y = (xy + wz) * xyz[0] + (1.0f - (xx + zz)) * xyz[1] + (yz - wx) * xyz[2];
    p->z = (xz - wy) * xyz[0] + (yz + wx) * xyz[1] + (1.0f - (xx + yy)) * xyz[2];
}
