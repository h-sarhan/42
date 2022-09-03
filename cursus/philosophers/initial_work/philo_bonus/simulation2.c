/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:35:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/03 22:40:32 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_fork(t_phil *phil, const unsigned int fork_idx,
								const bool old)
{
	bool	held;

	if (phil->sim->fork_takers[fork_idx] == 0
		|| phil->sim->fork_takers[fork_idx] != phil->num)
	{
		held = phil->sim->forks[fork_idx];
		sem_post(phil->sim->sems->num_forks);
		return (held);
	}
	else
		sem_post(phil->sim->sems->num_forks);
	return (old);
}

static int	eat_spaghetti(t_phil *phil)
{
	pick_up_fork(phil);
	
	if (log_action(phil->sim, phil->num, log_fork) == false)
		return (END);
	// printf("%d DIES HERE 1\n", phil->num);
	if (check_time_since_eat(phil) == END)
		return (END);
	// printf("%d DIES HERE 2\n", phil->num);
	pick_up_fork(phil);
	if (log_action(phil->sim, phil->num, log_fork) == false)
		return (END);
	
	if (check_time_since_eat(phil) == END)
		return (END);
	if (log_action(phil->sim, phil->num, log_eat) == false)
		return (END);
	// ! BROKEN
	if (phil->sim->min_eats > 0)
	{
		sem_wait(phil->sim->sems->num_eats[phil->num]);
		phil->num_eats++;
		sem_post(phil->sim->sems->num_eats[phil->num]);
	}
	gettimeofday(phil->phil_eat_time, NULL);
	if (sleepsleep(phil, phil->sim->time_to_eat * 1000) == FAIL)
		return (END);
	// check_sim_status(phil->sim->sems->status);
	put_back_fork(phil);
	put_back_fork(phil);
	
	if (check_time_since_eat(phil) == END)
		return (END);
	phil->state = EATING;
	return (CONTINUE);
}

int	eating_phase(t_phil *phil)
{
	if (eat_spaghetti(phil) == END)
		return (END);
	return (CONTINUE);
}
