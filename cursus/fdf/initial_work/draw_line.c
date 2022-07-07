/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 18:35:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_low(t_data *img, t_point *p1, t_point *p2, t_vars *vars)
{
	int	dxy[2];
	int	yi;
	int	d;
	int	xy[2];
	int	color;

	dxy[0] = p2->x - p1->x;
	dxy[1] = p2->y - p1->y;
	yi = 1;
	if (dxy[1] < 0)
	{
		yi = -1;
		dxy[1] = -dxy[1];
	}
	d = (2 * dxy[1]) - dxy[0];
	xy[1] = p1->y;
	xy[0] = p1->x;
	color = p1->color;
	while (xy[0] < p2->x)
	{
		if (p2->color == p1->color)
			my_mlx_pixel_put(img, xy[0], xy[1], p1->color, vars);
		else
		{
			color = color_mix(p1->color, p2->color,
					(float)(xy[0] - p1->x) / (p2->x - p1->x));
			my_mlx_pixel_put(img, xy[0], xy[1], color, vars);
		}
		if (d > 0)
		{
			xy[1] = xy[1] + yi;
			d = d + (2 * (dxy[1] - dxy[0]));
		}
		else
			d = d + 2 * dxy[1];
		xy[0]++;
	}
}

void	draw_line_high(t_data *img, t_point *p1, t_point *p2, t_vars *vars)
{
	int	dxy[2];
	int	xi;
	int	d;
	int	xy[2];
	int	color;

	dxy[0] = p2->x - p1->x;
	dxy[1] = p2->y - p1->y;
	xi = 1;
	if (dxy[0] < 0)
	{
		xi = -1;
		dxy[0] = -dxy[0];
	}
	d = (2 * dxy[0]) - dxy[1];
	xy[0] = p1->x;
	xy[1] = p1->y;
	color = p1->color;
	while (xy[1] < p2->y)
	{
		if (p2->color == p1->color)
			my_mlx_pixel_put(img, xy[0], xy[1], p1->color, vars);
		else
		{
			color = color_mix(p1->color, p2->color,
					(float)(xy[1] - p1->y) / (p2->y - p1->y));
			my_mlx_pixel_put(img, xy[0], xy[1], color, vars);
		}
		if (d > 0)
		{
			xy[0] = xy[0] + xi;
			d = d + (2 * (dxy[0] - dxy[1]));
		}
		else
			d = d + 2 * dxy[0];
		y++;
	}
}

void	draw_line(t_data *img, t_point *p1, t_point *p2, t_vars *vars)
{
	if (fabs(p2->y - p1->y) < fabs(p2->x - p1->x))
	{
		if (p1->x > p2->x)
			draw_line_low(img, p2, p1, vars);
		else
			draw_line_low(img, p1, p2, vars);
	}
	else
	{
		if (p1->y > p2->y)
			draw_line_high(img, p2, p1, vars);
		else
			draw_line_high(img, p1, p2, vars);
	}
}
