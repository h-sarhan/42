/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 19:07:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Log that a philosopher took a fork
void	log_fork(const t_sim *sim, const size_t phil_num, bool *success)
{
	t_time_ms	time;

	time = get_time(sim, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%lu %zu has taken a fork\n", time, phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}

// Log that a philosopher is eating
void	log_eat(const t_sim *sim, const size_t phil_num, bool *success)
{
	t_time_ms	time;

	time = get_time(sim, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%lu %zu is eating\n", time, phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}

// Log that a philosopher is sleeping
void	log_sleep(const t_sim *sim, const size_t phil_num, bool *success)
{
	t_time_ms	time;

	time = get_time(sim, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%lu %zu is sleeping\n", time, phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}

// Log that a philosopher is thinking
void	log_think(const t_sim *sim, const size_t phil_num, bool *success)
{
	t_time_ms	time;

	time = get_time(sim, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%lu %zu is thinking\n", time, phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}

// Log that a philosopher died
void	log_death(const t_sim *sim, const size_t phil_num, bool *success)
{
	t_time_ms	time;

	time = get_time(sim, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%lu %zu has died\n", time, phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}
