/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:40:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/02 09:19:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philosophers(t_sim *sim, bool *success)
{
	size_t	i;

	sim->forks = ft_calloc(sim->num_phils, sizeof(bool));
	if (sim->forks == NULL)
	{
		*success = false;
		return ;
	}
	i = 0;
	while (i < sim->num_phils)
		sim->forks[i++] = false;
	sim->phils = ft_calloc(sim->num_phils, sizeof(t_phil));
	if (sim->phils == NULL)
	{
		*success = false;
		return ;
	}
	i = 0;
	while (i < sim->num_phils)
		sim->phils[i++].state = THINKING;
	*success = true;
}
