/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/13 11:29:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Tests: 
// ? valgrind --tool=helgrind --history-level=none  ./philo 5 800 200 200 7
// * ./philo 1 800 200 200: Should not eat and die
// * ./philo 5 800 200 200 7: No one should die
// * ./philo 4 410 200 200: No one should die
// * ./philo 4 310 200 100: A philosopher should die
// Philosophers
// * ./philo 3 1000 500 600
// * ./philo 5 300 100 60
// * ./philo 5 200 100 60
// * ./philo 4 500 400 300
// * ./philo 3 700 200 200 Philosophers shouldnt die here

int	main(int argc, char **argv)
{
	t_sim		*sim;
	bool		success;
	t_phil		**philosophers;
	pthread_t	*threads;
	size_t		i;
	bool		all_ate;
	size_t		temp;

	sim = create_simulation();
	if (sim == NULL)
		return (EXIT_FAILURE);
	parse_args(sim, argc, argv, &success);
	if (!success)
	{
		write_to_stderror("Invalid arguments\n");
		free_sim(sim);
		return (EXIT_FAILURE);
	}
	philosophers = create_philosophers(sim);
	if (philosophers == NULL)
	{
		free_sim(sim);
		return (EXIT_FAILURE);
	}
	threads = ft_calloc(sim->num_phils, sizeof(pthread_t));
	if (threads == NULL)
	{
		free_philosophers(philosophers);
		free_sim(sim);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < sim->num_phils)
	{
		create_thread(&threads[i], run_sim, philosophers[i]);
		if (success == false)
		{
			free_philosophers(philosophers);
			free_sim(sim);
			ft_free(&threads);
			return (EXIT_FAILURE);
		}
		i++;
	}
	while (read_sim_status(sim) == true)
	{
		all_ate = true;
		if (sim->min_eats > 0)
		{
			i = 0;
			while (i < sim->num_phils)
			{
				lock_mutex(&philosophers[i]->num_eats_mutex);
				if (philosophers[i]->num_eats < sim->min_eats)
					all_ate = false;
				unlock_mutex(&philosophers[i]->num_eats_mutex);
				i++;
			}
			if (all_ate == true)
			{
				set_sim_status(sim, false);
				break ;
			}
		}
	}
	temp = 0;
	while (temp < sim->num_phils)
	{
		join_thread(&threads[temp], NULL);
		if (success == false)
		{
			free_philosophers(philosophers);
			free_sim(sim);
			ft_free(&threads);
			return (EXIT_FAILURE);
		}
		temp++;
	}
	temp = 0;
	while (temp < sim->num_phils)
	{
		free_mutex(&sim->fork_mutexes[temp]);
		temp++;
	}
	free_mutex(&sim->logging_mutex);
	free_mutex(&sim->status_mutex);
	free_philosophers(philosophers);
	free_sim(sim);
	ft_free(&threads);
	return (EXIT_SUCCESS);
}
