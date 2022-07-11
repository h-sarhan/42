/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:25:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/11 14:41:38 by hsarhan          ###   ########.fr       */
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
			// mlx_mouse_get_pos(vars->win, &vars->m_x, &vars->m_y);
			// if (vars->m_prev_x < vars->m_x)
			// 	rotate_x(vars->map, 2);
			// else if (vars->m_prev_x > vars->m_x)
			// 	rotate_x(vars->map, -2);
			// if (vars->m_prev_y < vars->m_y)
			// 	rotate_y(vars->map, 2);
			// else if (vars->m_prev_y > vars->m_y)
			// 	rotate_y(vars->map, -2);
			t_point m_direction;
			m_direction.x = (vars->m_x - vars->m_prev_x);
			m_direction.y = (vars->m_y - vars->m_prev_y);
			m_direction.z = 0;
			// float len = sqrt(pow(m_direction.x, 2) + pow(m_direction.y, 2) + pow(m_direction.z, 2));
			// if (len != 0)
			// {
			// 	m_direction.x /= len;
			// 	m_direction.y /= len;
			// 	m_direction.z /= len;
			// }
			// t_point *axis;
			// axis = cross_product(vars->map->look, &m_direction);
			// // TODO: TRY GETTING CROSS PRODUCT OF AXIS AND ORIENTATION
			// len = sqrt(pow(axis->x, 2) + pow(axis->y, 2) + pow(axis->z, 2));
			// if (len != 0)
			// {
			// 	axis->x /= len;
			// 	axis->y /= len;
			// 	axis->z /= len;
			// }
			// t_quaternion *q_rot = create_quaternion_rotation(2 * (PI / 180.0f), axis);
			// free(axis);
			// vars->map->orientation = rotate_quaternion(vars->map->orientation, q_rot);
			// rotate_points(vars->map);
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
