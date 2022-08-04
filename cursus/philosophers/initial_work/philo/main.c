/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/04 23:12:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


// Tests: 
// * 1 800 200 200: Should not eat and die
// * 5 800 200 200: No one should die
// * 4 410 200 200: No one should die
// * 4 310 200 200: A philosopher should die
// Philosophers

// ! Remove the calloc from get_start_time
int	main(int argc, char **argv)
{
	t_sim		*sim;
	bool		success;
	t_phil		**philosophers;
	pthread_t	*threads;
	size_t		i;

	sim = create_simulation();
	if (sim == NULL)
		return (EXIT_FAILURE);
	parse_args(sim, argc, argv, &success);
	if (!success)
	{
		write_to_stderror("Invalid arguments\n", NULL);
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
		create_thread(&threads[i], run_sim, philosophers[i], &success);
		if (success == false)
		{
			free_philosophers(philosophers);
			free_sim(sim);
			ft_free(&threads);
			return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (read_sim_status(sim, &success) == true)
		;
	size_t temp = 0;
	while (temp < sim->num_phils)
	{
		join_thread(&threads[temp], &success, NULL);
		free_mutex(&sim->fork_mutexes[temp], &success);
		if (success == false)
		{
			free_philosophers(philosophers);
			free_sim(sim);
			ft_free(&threads);
			return (EXIT_FAILURE);
		}
		temp++;
	}
	free_mutex(&sim->logging_mutex, &success);
	free_mutex(&sim->status_mutex, &success);
	free_philosophers(philosophers);
	free_sim(sim);
	ft_free(&threads);
	return (EXIT_SUCCESS);
}
