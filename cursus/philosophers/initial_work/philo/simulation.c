/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 12:29:13 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_simulation	*create_simulation(void)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (sim == NULL)
	{
		write_to_stderror("Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	sim->start_time = get_start_time();
	return (sim);
}

// Frees a simulation strucct
void	free_sim(t_simulation *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim);
}
