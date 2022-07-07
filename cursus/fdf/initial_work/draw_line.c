/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 12:40:37 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void draw_line_low(t_data *img, t_point *p1, t_point *p2, t_vars *vars)
{
	int dx;
	int dy;
	int yi;
	int d;
	int y;
	int x;
	int color;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = p1->y;
	x = p1->x;
	
	color = p1->color;
	while (x < p2->x)
	{
		if (p2->color == p1->color)
			my_mlx_pixel_put(img, x, y, p1->color, vars);
		else
		{
			// color = add_color(color, color1_diff);
			// color = add_color(color, color2_diff);
			color = color_mix(p1->color, p2->color, (float)(x - p1->x) / (p2->x - p1->x));
			my_mlx_pixel_put(img, x, y, color, vars);
		}
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		x++;
		// i++;
	}
}

void draw_line_high(t_data *img, t_point *p1, t_point *p2, t_vars *vars)
{
	int dx;
	int dy;
	int xi;
	int d;
	int y;
	int x;
	int color;
	

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = p1->x;
	y = p1->y;
	color = p1->color;
	while (y < p2->y)
	{
		if (p2->color == p1->color)
			// color = p1->color;
			my_mlx_pixel_put(img, x, y, p1->color, vars);
		else
		{
			// color = add_color(color, color1_diff);
			// color = add_color(color, color2_diff);
			color = color_mix(p1->color, p2->color, (float)(y - p1->y) / (p2->y - p1->y));
			my_mlx_pixel_put(img, x, y, color, vars);
		}
		if (d > 0)
		{
			x = x + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		y++;
	}
}

void draw_line(t_data *img, t_point *p1, t_point *p2, t_vars *vars)
{
	// printf("Drawing from (%d,%d) to (%d,%d)\n", p1->x, p1->y, p1->x, p2->y);
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
