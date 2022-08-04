/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/04 15:32:13 by hsarhan          ###   ########.fr       */
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
	// i = 0;
	// while (i < sim->num_phils)
	// {
	// 	set_phil_state(philosophers[i], DEAD, &success);
	// 	i++;
	// }
	size_t temp = 0;
	while (temp < sim->num_phils)
	{
		// if (temp != i)
		// 	detach_thread(&threads[temp], &success);
		// else
		join_thread(&threads[temp], &success, NULL);
		if (success == false)
		{
			free_philosophers(philosophers);
			free_sim(sim);
			ft_free(&threads);
			return (EXIT_FAILURE);
		}
		temp++;
	}
	free_philosophers(philosophers);
	free_sim(sim);
	ft_free(&threads);
	return (EXIT_SUCCESS);
}
