/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/02 09:22:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Get the start time of the simulation
t_timeval	*get_start_time(void)
{
	t_timeval	*start_time;

	start_time = ft_calloc(1, sizeof(t_timeval));
	if (start_time == NULL)
	{
		write_to_stderror("Failed to allocate memory\n", NULL);
		return (NULL);
	}
	if (gettimeofday(start_time, NULL) == FAIL)
	{
		write_to_stderror("Failed to get time\n", NULL);
		return (NULL);
	}
	return (start_time);
}

// Get the current time in ms
t_time_ms	get_time(const t_sim *sim, bool *success)
{
	t_timeval	curr_time;
	t_time_ms	curr_time_in_ms;
	t_time_ms	start_time_in_ms;

	start_time_in_ms = sim->start_time->tv_sec * 1000 + \
						sim->start_time->tv_usec / 1000;
	if (gettimeofday(&curr_time, NULL) == FAIL)
	{
		write_to_stderror("Failed to get time\n", NULL);
		*success = false;
		return (TIME_FAILURE);
	}
	curr_time_in_ms = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	*success = true;
	return (curr_time_in_ms - start_time_in_ms);
}
