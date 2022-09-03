/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/03 23:46:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_sim	*create_simulation(void)
{
	t_sim	*sim;

	sim = ft_calloc(1, sizeof(t_sim));
	if (sim == NULL)
		return (NULL);
	sim->start_time = ft_calloc(1, sizeof(t_timeval));
	if (sim->start_time == NULL)
		return (NULL);
	gettimeofday(sim->start_time, NULL);
	if (sim->start_time == NULL)
	{
		free_sim(sim);
		return (NULL);
	}
	return (sim);
}


void	*run_sim(void *phil_ptr)
{
	t_phil	*phil;

	phil = (t_phil *) phil_ptr;
	gettimeofday(phil->phil_eat_time, NULL);
	while (1)
	{
		if (phil->state == THINKING)
			if (eating_phase(phil) == END)
				exit(0);
		if (phil->state == EATING)
		{
			if (sleep_phase(phil) == END)
				exit(0);
			phil->state = SLEEPING;
			if (check_time_since_eat(phil) == END)
			{
				// printf("DIES HERE\n");
				exit(0);
			}
		}
		if (phil->state == SLEEPING)
			if (think_phase(phil) == END)
				exit(0);
		if (phil->state == DEAD)
			exit(0);
		// usleep(200);
		
	}
	exit(0);
}

// ! WRONG
unsigned int	read_num_eats(t_phil *phil)
{
	unsigned int	num_eats;

	sem_wait(phil->sim->sems->num_eats[phil->num]);
	num_eats = phil->num_eats;
	sem_post(phil->sim->sems->num_eats[phil->num]);
	return (num_eats);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->num_phils)
	{
		// pthread_mutex_destroy(&sim->fork_mutexes[i]);
		i++;
	}
	// pthread_mutex_destroy(&sim->logging_mutex);
	// pthread_mutex_destroy(&sim->status_mutex);
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	// ft_free(&sim->fork_mutexes);
	ft_free(&sim->fork_takers);
	ft_free(&sim);
}
