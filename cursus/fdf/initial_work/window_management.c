/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:25:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/11 16:57:57 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse_down(int key_code, int x, int y, void *params)
{
	t_vars	*vars;

	(void)x;
	(void)y;
	vars = params;
	// if (key_code == 3)
	// 	vars->m_down = 1;
	if (vars->m_down == 1)
	{
		vars->m_down = 0;
		// rotate_point(vars->map->orientation, vars->map->look);
	}
	else if (vars->m_down == 0)
		vars->m_down = 1;
	return (0);
}

int	handle_mouse_up(int key_code, int x, int y, void *params)
{
	t_vars	*vars;

	(void)x;
	(void)y;
	vars = params;
	if (key_code == 3)
		vars->m_down = 0;
	return (0);
}


t_point	*cross_product(t_point *v1, t_point *v2)
{
	t_point	*res;

	res = ft_calloc(1, sizeof(t_point));
	res->x = v1->y * v2->z - v1->z * v2->y;
	res->y = v1->z * v2->x - v1->x * v2->z;
	res->z = v1->x * v2->y - v1->y * v2->x;
	// free(v1);
	// free(v2);
	return (res);
}

int	mouse_rotate(void *params)
{
	t_vars	*vars;

	vars = params;
	if (vars->m_down == 1)
	{
		vars->m_prev_x = vars->m_x;
		vars->m_prev_y = vars->m_y;
		// mlx_mouse_get_pos(vars->mlx, vars->win, &vars->m_x, &vars->m_y);
		mlx_mouse_get_pos(vars->win, &vars->m_x, &vars->m_y);
		if (vars->m_x != vars->m_prev_x || vars->m_y != vars->m_prev_y)
		{
			mlx_mouse_get_pos(vars->win, &vars->m_x, &vars->m_y);
			if (vars->m_prev_x < vars->m_x)
				rotate_y(vars->map, -2);
			else if (vars->m_prev_x > vars->m_x)
				rotate_y(vars->map, 2);
			if (vars->m_prev_y < vars->m_y)
				rotate_x(vars->map, -2);
			else if (vars->m_prev_y > vars->m_y)
				rotate_x(vars->map, 2);
			rotate_points(vars->map);
			project_points(vars->map, vars->scale, vars->proj);
			draw_points(vars);
		}
	}
	return (0);
}

int	close_window(void *params)
{
	t_vars	*vars;

	vars = params;
	ft_putendl_fd("QUITTING PROGRAM!", 1);
	free_map(vars->map);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img);
	free(vars->data);
	free(vars->mlx);
	free(vars);
	exit(EXIT_SUCCESS);
	return (0);
}

void	*create_new_image(t_vars *vars)
{
	void	*old_image;

	old_image = vars->img;
	vars->data->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
	vars->img = vars->data->img;
	vars->data->addr = mlx_get_data_addr(vars->data->img,
			&vars->data->bits_per_pixel,
			&vars->data->line_length, &vars->data->endian);
	return (old_image);
}
