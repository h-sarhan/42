/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:45:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 14:55:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	read_fork_status(const t_sim *sim, const unsigned int fork_idx,
			bool *success)
{
	bool	fork_status;
	
	lock_mutex(&sim->fork_mutexes[fork_idx], success);
	fork_status = sim->forks[fork_idx];
	unlock_mutex(&sim->fork_mutexes[fork_idx], success);
	return (fork_status);
}

void	set_fork_status(t_sim *sim, const unsigned int fork_idx,
			const bool value, bool *success)
{
	
	lock_mutex(&sim->fork_mutexes[fork_idx], success);
	sim->forks[fork_idx] = value;
	unlock_mutex(&sim->fork_mutexes[fork_idx], success);
}
