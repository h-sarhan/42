/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/06 16:46:30 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Get the start time of the simulation
void	get_start_time(t_timeval *start_time)
{
	if (gettimeofday(start_time, NULL) == FAIL)
	{
		write_to_stderror("Failed to get time\n", NULL);
		return ;
	}
}

// Get the current time in ms
t_time_ms	get_time(const t_timeval *start_time, bool *success)
{
	t_timeval	curr_time;
	t_time_ms	curr_time_in_ms;
	t_time_ms	start_time_in_ms;

	start_time_in_ms = start_time->tv_sec * 1000 +  start_time->tv_usec / 1000;
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

unsigned long	get_micro_time(const t_timeval *start_time, bool *success)
{
	t_timeval		curr_time;
	unsigned long	curr_time_in_us;
	unsigned long	start_time_in_us;

	start_time_in_us = start_time->tv_sec * 1000000 + \
						start_time->tv_usec;
	if (gettimeofday(&curr_time, NULL) == FAIL)
	{
		write_to_stderror("Failed to get time\n", NULL);
		*success = false;
		return (TIME_FAILURE);
	}
	curr_time_in_us = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	*success = true;
	return (curr_time_in_us - start_time_in_us);
}
