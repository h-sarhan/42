/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 13:07:43 by hsarhan          ###   ########.fr       */
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
	unsigned int	fork_left;
	unsigned int	fork_right;
	bool			success;
	const t_phil	*phil;

	phil = (const t_phil *) phil_ptr;
	fork_left = phil->num;
	fork_right = phil->num + 1;
	if (phil->num == phil->sim->num_phils)
		fork_right = 1;
	
	log_eat(phil->sim, phil->num, &success);
	return (NULL);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	ft_free(&sim);
}
