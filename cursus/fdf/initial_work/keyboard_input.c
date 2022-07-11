/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/11 07:34:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_transformation_keys(int key, t_vars *vars)
{
	if ((key == KEY_LEFT || key == L_KEY_LEFT) && vars->proj != 'o')
		vars->map->rot_y -= 3;
	if ((key == KEY_RIGHT || key == L_KEY_RIGHT) && vars->proj != 'o')
		vars->map->rot_y += 3;
	if ((key == KEY_UP || key == L_KEY_UP) && vars->proj != 'o')
		vars->map->rot_x += 3;
	if ((key == KEY_DOWN || key == L_KEY_DOWN) && vars->proj != 'o')
		vars->map->rot_x -= 3;
	if (key == KEY_Q || key == L_KEY_Q)
		vars->map->rot_z += 3;
	if (key == KEY_E || key == L_KEY_E)
		vars->map->rot_z -= 3;
	if (key == KEY_W || key == L_KEY_W)
		vars->translate_y -= 10;
	if (key == KEY_A || key == L_KEY_A)
		vars->translate_x -= 10;
	if (key == KEY_S || key == L_KEY_S)
		vars->translate_y += 10;
	if (key == KEY_D || key == L_KEY_D)
		vars->translate_x += 10;
	if (key == KEY_PLUS || key == L_KEY_PLUS)
		vars->scale += 0.1;
	if (key == KEY_MINUS || key == L_KEY_MINUS)
		vars->scale -= 0.1;
}

void	check_projection_keys(int key, t_vars *vars)
{
	if (key == KEY_P || key == L_KEY_P)
	{
		if (vars->proj == 'i')
		{
			vars->proj = 'o';
			vars->map->rot_x = 0;
			vars->map->rot_y = 0;
			vars->map->rot_z = 90;
		}
		else if (vars->proj == 'o')
		{
			vars->proj = 'c';
			vars->map->rot_x = 0;
			vars->map->rot_y = 0;
			vars->map->rot_z = 0;
		}
		else if (vars->proj == 'c')
		{
			vars->proj = 'i';
			vars->map->rot_x = 0;
			vars->map->rot_y = 0;
			vars->map->rot_z = 0;
		}
	}
}

int	handle_keypress(int key, t_vars *vars)
{
	if (key == KEY_ESC || key == L_KEY_ESC)
		mlx_destroy_window(vars->mlx, vars->win);
	check_projection_keys(key, vars);
	check_transformation_keys(key, vars);
	if (key == KEY_LEFT || key == L_KEY_LEFT || key == KEY_RIGHT
		|| key == L_KEY_RIGHT || key == KEY_UP || key == L_KEY_UP
		|| key == KEY_DOWN || key == L_KEY_DOWN || key == KEY_Q
		|| key == L_KEY_Q || key == KEY_E || key == L_KEY_E || key == KEY_W
		|| key == L_KEY_W || key == KEY_A || key == L_KEY_A || key == KEY_S
		|| key == L_KEY_S || key == KEY_D || key == L_KEY_D || key == KEY_PLUS
		|| key == L_KEY_PLUS || key == KEY_MINUS || key == L_KEY_MINUS
		|| key == KEY_P || key == L_KEY_P)
	{
		rotate_points(vars->map, vars->map->rot_x * (PI / 180.0f),
			vars->map->rot_y * (PI / 180.0f), vars->map->rot_z * (PI / 180.0f));
		project_points(vars->map, vars->scale, vars->proj);
		draw_points(vars);
	}
	return (0);
}
