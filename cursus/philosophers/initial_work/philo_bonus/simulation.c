/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 10:13:17 by hsarhan          ###   ########.fr       */
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

static void	*check_time(void *phil_ptr)
{
	t_phil	*phil;

	phil = phil_ptr;
	while (1)
	{
		if (check_time_since_eat(phil) == END)
			break ;
		usleep(100);
	}
	// free_sim(phil->sim);
	// free_philosophers(phil->sim->philosophers);
	return (NULL);
}

void	*run_sim(void *phil_ptr)
{
	t_phil		*phil;
	pthread_t	thread;

	phil = phil_ptr;
	gettimeofday(phil->phil_eat_time, NULL);
	pthread_create(&thread, NULL, check_time, phil);
	while (1)
	{
		if (phil->state == THINKING)
			if (eating_phase(phil) == END)
				return (NULL);
		if (phil->state == EATING)
		{
			if (sleep_phase(phil) == END)
				return (NULL);
			phil->state = SLEEPING;
		}
		if (phil->state == SLEEPING)
			if (think_phase(phil) == END)
				return (NULL);
		if (phil->state == DEAD)
			return (NULL);
	}
	return (NULL);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	sem_unlink("/num_forks");
	sem_unlink("/logging");
	sem_unlink("/turn");
	sem_unlink("/time");
	sem_unlink("/num_eats");
	sem_close(sim->sems->logging);
	sem_close(sim->sems->num_eats);
	sem_close(sim->sems->num_forks);
	sem_close(sim->sems->time);
	sem_close(sim->sems->turn);
	ft_free(&sim->start_time);
	ft_free(&sim->sems);
	ft_free(&sim->philo_pids);
	ft_free(&sim);
}

t_sim	*init_sim(int argc, char **argv, t_phil ***philosophers)
{
	bool	success;
	t_sim	*sim;

	sim = create_simulation();
	if (sim == NULL)
		return (NULL);
	parse_args(sim, argc, argv, &success);
	if (success == false)
	{
		write(STDERR_FILENO, "Invalid arguments\n", 18);
		free_sim(sim);
		return (NULL);
	}
	*philosophers = create_philosophers(sim);
	if (*philosophers == NULL)
	{
		free_sim(sim);
		return (NULL);
	}
	return (sim);
}
