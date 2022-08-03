/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 14:01:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_sim	*create_simulation(void)
{
	t_sim	*sim;

	sim = ft_calloc(1, sizeof(t_sim));
	if (sim == NULL)
	{
		write_to_stderror("Failed to allocate memory\n", NULL);
		return (NULL);
	}
	sim->start_time = get_start_time();
	if (sim->start_time == NULL)
	{
		free_sim(sim);
		return (NULL);
	}
	return (sim);
}

// Starts the eat->think->sleep cycle of a philosopher
void	*run_sim(void *phil_ptr)
{
	unsigned int	left;
	unsigned int	right;
	bool			success;
	const t_phil	*phil;

	phil = (const t_phil *) phil_ptr;
	left = phil->num;
	right = phil->num + 1;
	success = true;
	if (phil->num == phil->sim->num_phils)
		right = 1;
	lock_mutex(phil->sim->fork_mutexes[left], &success);
	lock_mutex(phil->sim->fork_mutexes[right], &success);
	if (success == false)
	{
		// ! Do something
	}
	if (phil->sim->forks[left] == false && phil->sim->forks[right] == false)
	{
		phil->sim->forks[left] = true;
		phil->sim->forks[right] = true;
		usleep(phil->sim->time_to_sleep * 1000);
		log_eat(phil->sim, phil->num, &success);
	}
	phil->sim->forks[left] = false;
	phil->sim->forks[right] = false;
	unlock_mutex(phil->sim->fork_mutexes[right], &success);
	unlock_mutex(phil->sim->fork_mutexes[left], &success);
	if (success == false)
	{
		// ! Do something
	}
	return (NULL);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	ft_free(&sim);
}
