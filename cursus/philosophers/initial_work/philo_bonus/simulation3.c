/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:41:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 11:26:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think_phase(t_phil *phil)
{
	phil->state = THINKING;
	if (log_action(phil->sim, phil->num, "is thinking") == false)
		return (END);
	return (CONTINUE);
}

int	check_time_since_eat(t_phil *phil)
{
	t_phil	**philosophers;
	t_sim	*sim;

	sem_wait(phil->sim->sems->time);
	if (get_utime(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
	{
		philosophers = phil->sim->philosophers;
		sim = phil->sim;
		log_action(phil->sim, phil->num, "has died");
		sem_post(sim->sems->status);
		return (END);
	}
	sem_post(phil->sim->sems->time);
	return (CONTINUE);
}

int	sleep_phase(t_phil *phil)
{
	log_action(phil->sim, phil->num, "is sleeping");
	sleepsleep(phil, phil->sim->time_to_sleep * 1000);
	return (CONTINUE);
}

void	put_back_fork(t_phil *phil)
{
	sem_post(phil->sim->sems->num_forks);
}

void	pick_up_fork(t_phil *phil)
{
	sem_wait(phil->sim->sems->num_forks);
}
