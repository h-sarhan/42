/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:40:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 19:02:49 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philosophers(t_sim *sim, bool *success)
{
	size_t	i;

	sim->forks = malloc(sizeof(bool) * sim->num_phils);
	if (sim->forks == NULL)
	{
		*success = false;
		return ;
	}
	i = 0;
	while (i < sim->num_phils)
		sim->forks[i++] = false;
	sim->phils = malloc(sizeof(t_phil) * sim->num_phils);
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
