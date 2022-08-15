/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:41:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/15 09:10:26 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think_phase(t_phil *phil)
{
	phil->state = THINKING;
	if (read_sim_status(phil->sim) == true)
		log_action(phil->sim, phil->num, log_think);
	else
		return (END);
	if (check_time_since_eat(phil) == END)
		return (END);
	return (CONTINUE);
}

int	check_time_since_eat(t_phil *phil)
{
	if (get_mtime(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
	{
		phil->state = DEAD;
		pthread_mutex_lock(&phil->sim->status_mutex);
		if (phil->sim->status == true)
		{
			phil->sim->status = false;
			pthread_mutex_unlock(&phil->sim->status_mutex);
			log_action(phil->sim, phil->num, log_death);
		}
		else
			pthread_mutex_unlock(&phil->sim->status_mutex);
		return (END);
	}
	return (CONTINUE);
}

int	sleep_phase(t_phil *phil)
{
	log_action(phil->sim, phil->num, log_sleep);
	if (phil->sim->time_to_sleep * 1000 + get_mtime(phil->phil_eat_time)
		>= phil->sim->time_to_die * 1000)
	{
		phil->state = DEAD;
		if (sleepsleep(phil, (phil->sim->time_to_die * 1000 - \
				get_mtime(phil->phil_eat_time))) == FAIL)
			return (END);
		pthread_mutex_lock(&phil->sim->status_mutex);
		if (phil->sim->status == true)
		{
			phil->sim->status = false;
			pthread_mutex_unlock(&phil->sim->status_mutex);
			log_action(phil->sim, phil->num, log_death);
		}
		else
			pthread_mutex_unlock(&phil->sim->status_mutex);
		return (END);
	}
	if (read_sim_status(phil->sim) == false
		|| sleepsleep(phil, phil->sim->time_to_sleep * 1000) == FAIL
		|| check_time_since_eat(phil) == END)
		return (END);
	return (CONTINUE);
}

void	put_back_forks(t_phil *phil, const unsigned int left,
							const unsigned int right)
{
	if (right == 0 || phil->num % 2 == 0)
	{
		pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
		pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
	}
	else
	{
		pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
		pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
	}
	phil->sim->forks[right] = false;
	pthread_mutex_unlock(&phil->sim->fork_mutexes[right]);
	phil->sim->forks[left] = false;
	pthread_mutex_unlock(&phil->sim->fork_mutexes[left]);
}

void	pick_up_forks(t_phil *phil, const unsigned int left,
						const unsigned int right)
{
	if (right == 0 || phil->num % 2 == 0)
	{
		pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
		pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
	}
	else
	{
		pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
		pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
	}
	phil->sim->forks[left] = true;
	phil->sim->fork_takers[left] = phil->num;
	pthread_mutex_unlock(&phil->sim->fork_mutexes[left]);
	phil->sim->forks[right] = true;
	phil->sim->fork_takers[right] = phil->num;
	pthread_mutex_unlock(&phil->sim->fork_mutexes[right]);
}
