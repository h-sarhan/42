/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 13:53:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_sim	*create_simulation(void)
{
	t_sim	*sim;

	sim = malloc(sizeof(t_sim));
	if (sim == NULL)
	{
		write_to_stderror("Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	sim->start_time = get_start_time();
	if (sim->start_time == NULL)
	{
		free_sim(sim);
		exit(EXIT_FAILURE);
	}
	return (sim);
}

// Frees a simulation strucct
void	free_sim(t_sim *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim);
}
