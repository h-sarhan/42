/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:40:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 16:22:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_phil	*create_philosopher(t_sim *sim, const unsigned int num)
{
	t_phil	*phil;
	bool	success;

	phil = ft_calloc(1, sizeof(t_phil));
	if (phil == NULL)
		return (NULL);
	phil->num = num;
	phil->sim = sim;
	phil->state = THINKING;
	phil->state_mutex = create_mutex(&success);
	if (success == false)
	{
		// ! do something
	}
	return (phil);
}

t_phil	**create_philosophers(t_sim *sim)
{
	t_phil			**phils;
	unsigned int	num;
	unsigned int	temp;
	bool			success;

	num = 0;
	phils = ft_calloc(sim->num_phils, sizeof(t_sim *));
	success = true;
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
			ft_free(&phils);
			return (NULL);
		}
		num++;
	}
	create_forks(sim, &success);
	if (success == false)
	{
		temp = 0;
		while (temp < sim->num_phils)
		{
			ft_free(&phils[temp]);
			temp++;
		}
		ft_free(&phils);
		return (NULL);
	}
	return (phils);
}

void	create_forks(t_sim *sim, bool *success)
{
	unsigned int	i;
	unsigned int	temp;

	i = 0;
	sim->forks = ft_calloc(sim->num_phils + 1, sizeof(bool));
	if (sim->forks == NULL)
	{
		*success = false;
		return ;
	}
	sim->fork_mutexes = ft_calloc(sim->num_phils + 1, sizeof(pthread_mutex_t));
	if (sim->fork_mutexes == NULL)
	{
		*success = false;
		return ;
	}
	while (i < sim->num_phils)
	{
		sim->fork_mutexes[i] = create_mutex(success);
		sim->forks[i] = false;
		if (*success == false)
		{
			temp = 0;
			while (temp < i)
			{
				free_mutex(&sim->fork_mutexes[temp], success);
				temp++;
			}
			ft_free(&sim->fork_mutexes);
			return ;
		}
		i++;
	}
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
