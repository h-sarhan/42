/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:35:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 11:47:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eat_spaghetti(t_phil *phil)
{
	sem_wait(phil->sim->sems->turn);
	pick_up_fork(phil);
	if (log_action(phil->sim, phil->num, "has taken a fork") == false)
		return (END);
	pick_up_fork(phil);
	if (log_action(phil->sim, phil->num, "has taken a fork") == false)
		return (END);
	if (log_action(phil->sim, phil->num, "is eating") == false)
		return (END);
	sem_post(phil->sim->sems->turn);
	sem_wait(phil->sim->sems->time);
	gettimeofday(phil->phil_eat_time, NULL);
	sem_post(phil->sim->sems->time);
	if (sleepsleep(phil, phil->sim->time_to_eat * 1000) == FAIL)
		return (END);
	put_back_fork(phil);
	put_back_fork(phil);
	phil->state = EATING;
	if (phil->sim->min_eats > 0)
	{
		phil->num_eats++;
		if (phil->num_eats == phil->sim->min_eats)
			sem_post(phil->sim->sems->num_eats);
	}
	return (CONTINUE);
}

int	eating_phase(t_phil *phil)
{
	if (eat_spaghetti(phil) == END)
		return (END);
	return (CONTINUE);
}