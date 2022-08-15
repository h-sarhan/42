/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/15 13:05:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Log that a philosopher is eating
void	log_eat(const t_time_ms *time, const size_t phil_num)
{
	printf("%-4lu %-3zu has taken a fork\n", *time, phil_num);
	printf("%-4lu %-3zu has taken a fork\n", *time, phil_num);
	printf("%-4lu %-3zu is eating\n", *time, phil_num);
}

// Log that a philosopher is sleeping
void	log_sleep(const t_time_ms *time, const size_t phil_num)
{
	printf("%-4lu %-3zu is sleeping\n", *time, phil_num);
}

// Log that a philosopher is thinking
void	log_think(const t_time_ms *time, const size_t phil_num)
{
	printf("%-4lu %-3zu is thinking\n", *time, phil_num);
}

// Log that a philosopher died
void	log_death(const t_time_ms *time, const size_t phil_num)
{
	printf("%-4lu %-3zu has died\n", *time, phil_num);
}

bool	log_action(t_sim *sim, const size_t phil_num, t_log_func f)
{
	t_time_ms	time;
	bool		status;

	if (f == log_death)
	{
		// pthread_mutex_lock(&sim->logging_mutex);
		time = get_time(sim->start_time);
		f(&time, phil_num);
		// pthread_mutex_unlock(&sim->logging_mutex);
		return (false);
	}
	// pthread_mutex_lock(&sim->status_mutex);
	status = sim->status;
	// pthread_mutex_unlock(&sim->status_mutex);
	if (status == true || f == log_death)
	{
		// pthread_mutex_lock(&sim->logging_mutex);
		time = get_time(sim->start_time);
		f(&time, phil_num);
		// pthread_mutex_unlock(&sim->logging_mutex);
	}
	return (status);
}
