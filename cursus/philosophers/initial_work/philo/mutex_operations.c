/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:45:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/08 09:53:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	read_fork_status(const t_sim *sim, const unsigned int fork_idx)
{
	bool	fork_status;

	lock_mutex(&sim->fork_mutexes[fork_idx]);
	fork_status = sim->forks[fork_idx];
	unlock_mutex(&sim->fork_mutexes[fork_idx]);
	return (fork_status);
}

void	set_fork_status(t_sim *sim, const unsigned int fork_idx,
			const bool value)
{
	lock_mutex(&sim->fork_mutexes[fork_idx]);
	sim->forks[fork_idx] = value;
	unlock_mutex(&sim->fork_mutexes[fork_idx]);
}

// t_phil_state	read_phil_state(t_phil *phil, )
// {
// 	t_phil_state	phil_state;

// 	// lock_mutex(&phil->state_mutex, success);
// 	phil_state = phil->state;
// 	// unlock_mutex(&phil->state_mutex, success);
// 	return (phil_state);
// }

// void	set_phil_state(t_phil *phil, const t_phil_state state, )
// {
// 	// lock_mutex(&phil->state_mutex, success);
// 	phil->state = state;
// 	// unlock_mutex(&phil->state_mutex, success);
// }
