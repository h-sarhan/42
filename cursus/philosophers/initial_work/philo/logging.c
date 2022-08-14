/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/14 11:49:33 by hsarhan          ###   ########.fr       */
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

void	log_action(t_sim *sim, const size_t phil_num, t_log_func f)
{
	t_time_ms	time;

	pthread_mutex_lock(&sim->logging_mutex);
	pthread_mutex_lock(&sim->status_mutex);
	time = get_time(sim->start_time);
	if (sim->status == true || f == log_death)
	{
		pthread_mutex_unlock(&sim->status_mutex);
		f(&time, phil_num);
	}
	else
		pthread_mutex_unlock(&sim->status_mutex);
	pthread_mutex_unlock(&sim->logging_mutex);
}
