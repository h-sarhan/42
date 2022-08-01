/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 13:55:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Log that a philosopher took a fork
void	log_fork(t_sim *sim, size_t phil_num)
{
	if (printf("%lu %zu has taken a fork\n", get_time(sim), phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n");
		free_sim(sim);
		exit(EXIT_FAILURE);
	}
}

// Log that a philosopher is eating
void	log_eat(t_sim *sim, size_t phil_num)
{
	if (printf("%lu %zu is eating\n", get_time(sim), phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n");
		free_sim(sim);
	}
}

// Log that a philosopher is sleeping
void	log_eat(t_sim *sim, size_t phil_num)
{
	if (printf("%lu %zu is sleeping\n", get_time(sim), phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n");
		free_sim(sim);
	}
}

// Log that a philosopher is thinking
void	log_think(t_sim *sim, size_t phil_num)
{
	if (printf("%lu %zu is thinking\n", get_time(sim), phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n");
		free_sim(sim);
	}
}

// Log that a philosopher died
void	log_death(t_sim *sim, size_t phil_num)
{
	if (printf("%lu %zu has died\n", get_time(sim), phil_num) < SUCCESS)
	{
		write_to_stderror("Logging failure\n");
		free_sim(sim);
	}
}
