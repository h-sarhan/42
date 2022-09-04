/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:41:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 17:22:23 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think_phase(t_phil *phil)
{
	phil->state = THINKING;
	log_action(phil->sim, phil->num, "is thinking");
}

int	check_time_since_eat(t_phil *phil)
{
	if (sem_wait(phil->sim->sems->time) != 0)
		perror(NULL);
	if (get_utime(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
	{
		sem_post(phil->sim->sems->time);
		log_action(phil->sim, phil->num, "has died");
		sem_post(phil->sim->sems->status);
		return (END);
	}
	sem_post(phil->sim->sems->time);
	return (CONTINUE);
}

void	sleep_phase(t_phil *phil)
{
	log_action(phil->sim, phil->num, "is sleeping");
	sleepsleep(phil, phil->sim->time_to_sleep * 1000);
	phil->state = SLEEPING;
}

void	put_back_fork(t_phil *phil)
{
	if (sem_post(phil->sim->sems->num_forks) != 0)
		perror(NULL);
}

void	pick_up_fork(t_phil *phil)
{
	if (sem_wait(phil->sim->sems->num_forks) != 0)
		perror(NULL);
}
