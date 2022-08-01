/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 13:10:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Get the start time of the simulation
struct timeval	*get_start_time(void)
{
	struct timeval	*start_time;

	start_time = malloc(sizeof(struct timeval));
	if (start_time == NULL)
	{
		write_to_stderror("Failed to allocate memory\n");
		return (NULL);
	}
	if (gettimeofday(start_time, NULL) == FAIL)
	{
		write_to_stderror("Failed to get time\n");
		return (NULL);
	}
	return (start_time);
}

// Get the current time in ms
t_time_ms	get_time(t_simulation *sim)
{
	struct timeval	curr_time;
	t_time_ms		curr_time_in_ms;
	t_time_ms		start_time_in_ms;

	start_time_in_ms = sim->start_time->tv_sec * 1000 + \
						sim->start_time->tv_usec / 1000;
	if (gettimeofday(&curr_time, NULL) == FAIL)
	{
		write_to_stderror("Failed to get time\n");
		free_sim(sim);
		exit(EXIT_FAILURE);
	}
	curr_time_in_ms = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (curr_time_in_ms - start_time_in_ms);
}
