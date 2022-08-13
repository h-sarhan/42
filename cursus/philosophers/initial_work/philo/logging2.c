/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:14:16 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/13 12:37:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_action(t_sim *sim, const size_t phil_num, t_log_func f)
{
	t_time_ms	time;

	time = get_time(sim->start_time);
	if (read_sim_status(sim) == true || f == log_death)
	{
		pthread_mutex_lock(&sim->logging_mutex);
		f(&time, phil_num);
		pthread_mutex_unlock(&sim->logging_mutex);
	}
}
