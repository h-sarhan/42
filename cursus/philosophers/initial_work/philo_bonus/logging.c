/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/03 22:40:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Log that a philosopher is eating
void	log_eat(const t_time_ms *time, const size_t phil_num)
{
	// printf("%-4lu %-3zu has taken a fork\n", *time, phil_num);
	// printf("%-4lu %-3zu has taken a fork\n", *time, phil_num);
	printf("%-4lu %-3zu is eating\n", *time, phil_num);
}

void	log_fork(const t_time_ms *time, const size_t phil_num)
{
	printf("%-4lu %-3zu has taken a fork\n", *time, phil_num);
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

	// sem_wait(sim->sems->status);
	// status = sim->status;
	// if (status == true || f == log_death)
	// {
		// sem_post(sim->sems->status);
	sem_wait(sim->sems->logging);
	time = get_time(sim->start_time);
	f(&time, phil_num);
	sem_post(sim->sems->logging);
	// }
	// else
	// 	sem_post(sim->sems->status);
	if (f == log_death)
		return (false);
	return (true);
}
