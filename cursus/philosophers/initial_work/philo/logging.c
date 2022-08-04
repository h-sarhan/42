/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/04 23:05:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Log that a philosopher took a fork
void	log_fork(const t_sim *sim, const size_t phil_num, bool *success)
{
	t_time_ms	time;

	time = get_time(sim->start_time, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%-4lu %-3zu has taken a fork\n", time, phil_num) < SUCCESS)
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

	time = get_time(sim->start_time, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%-4lu %-3zu is eating\n", time, phil_num) < SUCCESS)
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

	time = get_time(sim->start_time, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%-4lu %-3zu is sleeping\n", time, phil_num) < SUCCESS)
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

	time = get_time(sim->start_time, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%-4lu %-3zu is thinking\n", time, phil_num) < SUCCESS)
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

	time = get_time(sim->start_time, success);
	if (!success)
	{
		write_to_stderror("Logging failure\n", NULL);
		return ;
	}
	if (printf("%-4lu %-3zu has died\n", time, phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}

void	log_action(t_sim *sim, const size_t phil_num, bool *succ, t_log_func f)
{
	// if (read_sim_status(sim, succ) == true)
	// {
		lock_mutex(&sim->logging_mutex, succ);
		f(sim, phil_num, succ);
		// usleep(100);
		unlock_mutex(&sim->logging_mutex, succ);
	// }
}
