/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:16:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 16:59:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	add_color(int color1, int color2)
{
	int	new_color;

	new_color = create_trgb(min(get_t(color1) + get_t(color1), 255),
			min(get_r(color1) + get_r(color2), 255),
			min(get_g(color1) + get_g(color2), 255),
			min(get_b(color1) + get_b(color2), 255));
	return (new_color);
}

int	color_mix(int c1, int c2, float mix)
{
	int	result;
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(c1) * (1 - mix) + get_t(c2) * mix;
	r = get_r(c1) * (1 - mix) + get_r(c2) * mix;
	g = get_g(c1) * (1 - mix) + get_g(c2) * mix;
	b = get_b(c1) * (1 - mix) + get_b(c2) * mix;
	result = create_trgb(t, r, g, b);
	return (result);
}
