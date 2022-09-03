/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:35:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/03 21:28:46 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_fork(t_phil *phil, const unsigned int fork_idx,
								const bool old)
{
	bool	held;

	// printf("BEfpre waiting\n");
	// sem_wait(phil->sim->sems->num_forks);
	// printf("After waiting\n");
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

// static int	look_for_fork(t_phil *phil, const unsigned int fork_idx)
// {
// 	bool	fork_status;

// 	fork_status = true;
// 	while (fork_status == true)
// 	{
// 		fork_status = check_fork(phil, fork_idx, fork_status);
// 		if (fork_status == false)
// 			break ;
// 		if (check_time_since_eat(phil) == END)
// 			return (END);
// 	}
// 	return (CONTINUE);
// }

static int	eat_spaghetti(t_phil *phil)
{
	// if (check_time_since_eat(phil) == END)
	// 	return (END);
	pick_up_fork(phil);
	pick_up_fork(phil);
	if (log_action(phil->sim, phil->num, log_eat) == false)
		return (END);
	if (phil->sim->min_eats > 0)
	{
		sem_wait(phil->sim->sems->num_eats[phil->num]);
		phil->num_eats++;
		sem_post(phil->sim->sems->num_eats[phil->num]);
	}
	gettimeofday(phil->phil_eat_time, NULL);
	if (sleepsleep(phil, phil->sim->time_to_eat * 1000) == FAIL)
		return (END);
	put_back_fork(phil);
	put_back_fork(phil);
	phil->state = EATING;
	return (CONTINUE);
}

int	eating_phase(t_phil *phil)
{
	if (eat_spaghetti(phil) == END)
		return (END);
	return (CONTINUE);
}
