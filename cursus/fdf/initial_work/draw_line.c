/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/30 22:30:01 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_line_low(t_data *img, int x0, int y0, int x1, int y1, unsigned int color)
{
	int dx;
	int dy;
	int yi;
	int d;
	int y;
	int x;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = y0;
	x = x0;
	while (x <= x1)
	{
		// if ((color >> 24) < 60)
		// 	color += (1 << 24) * 1;
		my_mlx_pixel_put(img, x, y,color);
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		x++;
	}
}

void draw_line_high(t_data *img, int x0, int y0, int x1, int y1, unsigned int color)
{
	int dx;
	int dy;
	int xi;
	int d;
	int y;
	int x;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = x0;
	y = y0;
	while (y <= y1)
	{
		// if ((color >> 24) < 100)
		// 	color += (1 << 24) * 1;
		
		my_mlx_pixel_put(img, x, y, color);
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


// TODO: INTERPOLATE COLOR MAYBE
// TODO: MAKE THIS ACCEPT TWO POINTS
void draw_line(t_data *img, int x0, int y0, int x1, int y1, unsigned int color)
{
	// printf("Drawing from (%d,%d) to (%d,%d)\n", x0, y0, x1, y1);
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			draw_line_low(img, x1, y1, x0, y0, color);
		else
			draw_line_low(img, x0, y0, x1, y1, color);
	}
	else
	{
		if (y0 > y1)
			draw_line_high(img, x1, y1, x0, y0, color);
		else
			draw_line_high(img, x0, y0, x1, y1, color);
	} 
}
