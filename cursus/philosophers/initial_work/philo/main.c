/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 17:01:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Philosophers
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
		threads[i] = create_thread(run_sim, philosophers[i], &success);
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
	// while (philosophers[i % sim->num_phils]->state != DEAD)
	while (read_phil_state(philosophers[i % sim->num_phils], &success) != DEAD)
		i++;
	return (EXIT_SUCCESS);
	while (i < sim->num_phils)
	{
		detach_thread(&threads[i], &success);
		// join_thread(&threads[i], &success, NULL);
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
	// ! THIS CAUSES BIG SEG FAULTS
	// free_philosophers(philosophers);
	// free_sim(sim);
	// ft_free(&threads);
	return (EXIT_SUCCESS);
}
