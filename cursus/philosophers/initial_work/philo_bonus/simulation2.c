/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:35:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 12:47:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_phase(t_phil *phil)
{
	if (sem_wait(phil->sim->sems->turn) != 0)
		perror(NULL);
	pick_up_fork(phil);
	log_action(phil->sim, phil->num, "has taken a fork");
	pick_up_fork(phil);
	log_action(phil->sim, phil->num, "has taken a fork");
	log_action(phil->sim, phil->num, "is eating");
	sem_post(phil->sim->sems->turn);
	if (sem_wait(phil->sim->sems->time) != 0)
		perror(NULL);
	gettimeofday(phil->phil_eat_time, NULL);
	sem_post(phil->sim->sems->time);
	sleepsleep(phil, phil->sim->time_to_eat * 1000);
	put_back_fork(phil);
	put_back_fork(phil);
	phil->state = EATING;
	if (phil->sim->min_eats > 0)
	{
		phil->num_eats++;
		if (phil->num_eats == phil->sim->min_eats)
			sem_post(phil->sim->sems->num_eats);
	}
}
