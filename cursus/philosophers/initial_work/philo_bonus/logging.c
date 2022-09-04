/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:39:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 12:02:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	log_action(t_sim *sim, const size_t phil_num, const char *action)
{
	t_time_ms	time;

	sem_wait(sim->sems->logging);
	time = get_time(sim->start_time);
	printf("%-4lu %-3zu %s\n", time, phil_num, action);
	if (ft_strncmp(action, "has died", ft_strlen(action)) != 0)
		sem_post(sim->sems->logging);
	return (true);
}
