/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:40:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/02 10:55:48 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_phil	*create_philosopher(t_sim *sim, const unsigned int num)
{
	t_phil	*phil;

	phil = ft_calloc(1, sizeof(t_phil));
	if (phil == NULL)
		return (NULL);
	phil->num = num;
	phil->sim = sim;
	phil->state = THINKING;
	return (phil);
}

t_phil	**create_philosophers(t_sim *sim)
{
	t_phil			**phils;
	unsigned int	num;
	unsigned int	temp;

	num = 0;
	phils = ft_calloc(sim->num_phils, sizeof(t_sim *));
	if (phils == NULL)
		return (NULL);
	while (num < sim->num_phils)
	{
		phils[num] = create_philosopher(sim, num + 1);
		if (phils[num] == NULL)
		{
			temp = 0;
			while (temp < num)
			{
				ft_free(&phils[temp]);
				temp++;
			}
			return (NULL);
		}
		num++;
	}
	return (phils);
}

void	free_philosophers(t_phil **phils)
{
	unsigned int	num_phils;
	unsigned int	i;

	num_phils = phils[0]->sim->num_phils;
	i = 0;
	while (i < num_phils)
	{
		ft_free(&phils[i]);
		i++;
	}
	ft_free(&phils);
}