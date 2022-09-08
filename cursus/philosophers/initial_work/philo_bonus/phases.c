/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phases.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:41:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/09 01:47:51 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think_phase(t_phil *phil)
{
	phil->state = THINKING;
	log_action(phil->sim, phil->num, "is thinking");
}

void	sleep_phase(t_phil *phil)
{
	log_action(phil->sim, phil->num, "is sleeping");
	sleepsleep(phil, phil->sim->time_to_sleep * 1000);
	phil->state = SLEEPING;
}

void	eating_phase(t_phil *phil)
{
	sem_wait(phil->sim->sems->turn);
	sem_wait(phil->sim->sems->num_forks);
	log_action(phil->sim, phil->num, "has taken a fork");
	sem_wait(phil->sim->sems->num_forks);
	log_action(phil->sim, phil->num, "has taken a fork");
	log_action(phil->sim, phil->num, "is eating");
	sem_post(phil->sim->sems->turn);
	phil->state = EATING;
	if (phil->sim->min_eats > 0)
	{
		phil->num_eats++;
		if (phil->num_eats == phil->sim->min_eats)
			sem_post(phil->sim->sems->num_eats);
	}
	sem_wait(phil->sim->sems->time);
	gettimeofday(phil->phil_eat_time, NULL);
	sem_post(phil->sim->sems->time);
	sleepsleep(phil, phil->sim->time_to_eat * 1000);
	sem_post(phil->sim->sems->num_forks);
	sem_post(phil->sim->sems->num_forks);
}
