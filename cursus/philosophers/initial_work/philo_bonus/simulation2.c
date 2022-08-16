/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 15:35:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/16 15:54:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static bool	check_right_fork(t_phil *phil, const unsigned int left,
// 							const unsigned int right, const bool old)
// {
// 	bool	held;

// 	if (left == right)
// 		return (true);
// 	// pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
// 	if (phil->sim->fork_takers[right] == 0
// 		|| phil->sim->fork_takers[right] != phil->num)
// 	{
// 		held = phil->sim->forks[right];
// 		// pthread_mutex_unlock(&phil->sim->fork_mutexes[right]);
// 		return (held);
// 	}
// 	else
// 		// pthread_mutex_unlock(&phil->sim->fork_mutexes[right]);
// 	return (old);
// }

static bool	check_fork(t_phil *phil, const unsigned int fork_idx,
								const bool old)
{
	bool	held;

	// pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
	if (phil->sim->fork_takers[fork_idx] == 0
		|| phil->sim->fork_takers[fork_idx] != phil->num)
	{
		held = phil->sim->forks[fork_idx];
		// pthread_mutex_unlock(&phil->sim->fork_mutexes[left]);
		return (held);
	}
	else
		// pthread_mutex_unlock(&phil->sim->fork_mutexes[left]);
	return (old);
}

static int	look_for_fork(t_phil *phil, const unsigned int fork_idx)
{
	bool	fork_status;

	fork_status = true;
	while (fork_status == true)
	{
		fork_status = check_fork(phil, fork_idx, fork_status);
		if (fork_status == false)
			break ;
		if (check_time_since_eat(phil) == END)
			return (END);
	}
	return (CONTINUE);
}

static int	eat_spaghetti(t_phil *phil, const unsigned int fork_idx)
{
	if (check_time_since_eat(phil) == END)
		return (END);
	pick_up_fork(phil, fork_idx);
	if (log_action(phil->sim, phil->num, log_eat) == false)
		return (END);
	if (phil->sim->min_eats > 0)
	{
		// pthread_mutex_lock(&phil->num_eats_mutex);
		phil->num_eats++;
		// pthread_mutex_unlock(&phil->num_eats_mutex);
	}
	gettimeofday(phil->phil_eat_time, NULL);
	if (sleepsleep(phil, phil->sim->time_to_eat * 1000) == FAIL)
		return (END);
	put_back_fork(phil, fork_idx);
	phil->state = EATING;
	return (CONTINUE);
}

int	eating_phase(t_phil *phil)
{
	unsigned int	fork_idx;

	fork_idx = phil->num - 1;
	if (look_for_fork(phil, fork_idx) == END)
		return (END);
	if (eat_spaghetti(phil, fork_idx) == END)
		return (END);
	return (CONTINUE);
}
