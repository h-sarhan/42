/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/13 14:13:24 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_sim	*create_simulation(void)
{
	t_sim	*sim;

	sim = ft_calloc(1, sizeof(t_sim));
	if (sim == NULL)
		return (NULL);
	sim->start_time = ft_calloc(1, sizeof(t_timeval));
	if (sim->start_time == NULL)
		return (NULL);
	gettimeofday(sim->start_time, NULL);
	pthread_mutex_init(&sim->logging_mutex, NULL);
	pthread_mutex_init(&sim->status_mutex, NULL);
	if (sim->start_time == NULL)
	{
		free_sim(sim);
		return (NULL);
	}
	sim->status = true;
	return (sim);
}

bool	read_sim_status(t_sim *sim)
{
	bool	status;

	pthread_mutex_lock(&sim->status_mutex);
	status = sim->status;
	pthread_mutex_unlock(&sim->status_mutex);
	return (status);
}

void	set_sim_status(t_sim *sim, const bool status)
{
	pthread_mutex_lock(&sim->status_mutex);
	sim->status = status;
	pthread_mutex_unlock(&sim->status_mutex);
}

void	*run_sim(void *phil_ptr)
{
	unsigned int	left;
	unsigned int	right;
	t_phil			*phil;
	bool			left_held;
	bool			right_held;

	phil = (t_phil *) phil_ptr;
	gettimeofday(phil->phil_eat_time, NULL);
	if (phil->sim->num_phils == 1)
	{
		left = 0;
		right = 0;
	}
	else
	{
		left = phil->num - 1;
		right = phil->num;
	}
	if (phil->num == phil->sim->num_phils)
		right = 0;
	left_held = true;
	right_held = true;
	while (1)
	{
		if (phil->state == THINKING)
		{
			left_held = true;
			right_held = true;
			while ((left_held == true || right_held == true))
			{
				if (right == 0 || phil->num % 2 == 0)
				{
					if (left == right)
						right_held = true;
					else
					{
						pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
						if (phil->sim->fork_takers[right] == 0
							|| phil->sim->fork_takers[right] != phil->num)
							right_held = phil->sim->forks[right];
					}
					pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
					if (phil->sim->fork_takers[left] == 0
						|| phil->sim->fork_takers[left] != phil->num)
						left_held = phil->sim->forks[left];
				}
				else
				{
					pthread_mutex_lock(&phil->sim->fork_mutexes[left]);
					if (phil->sim->fork_takers[left] == 0
						|| phil->sim->fork_takers[left] != phil->num)
						left_held = phil->sim->forks[left];
					if (left == right)
						right_held = true;
					else
					{
						pthread_mutex_lock(&phil->sim->fork_mutexes[right]);
						if (phil->sim->fork_takers[right] == 0
							|| phil->sim->fork_takers[right] != phil->num)
							right_held = phil->sim->forks[right];
					}
				}
				if (left_held == false && right_held == false)
					break ;
				if (left != right)
					pthread_mutex_unlock(&phil->sim->fork_mutexes[right]);
				pthread_mutex_unlock(&phil->sim->fork_mutexes[left]);
				if (get_mtime(phil->phil_eat_time)
					>= phil->sim->time_to_die * 1000)
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
					return (NULL);
				}
			}
			phil->sim->forks[left] = true;
			phil->sim->forks[right] = true;
			phil->sim->fork_takers[right] = phil->num;
			phil->sim->fork_takers[left] = phil->num;
			pthread_mutex_unlock(&phil->sim->fork_mutexes[right]);
			pthread_mutex_unlock(&phil->sim->fork_mutexes[left]);
			if (read_sim_status(phil->sim) == false)
				return (NULL);
			log_action(phil->sim, phil->num, log_eat);
			pthread_mutex_lock(&phil->num_eats_mutex);
			phil->num_eats++;
			pthread_mutex_unlock(&phil->num_eats_mutex);
			gettimeofday(phil->phil_eat_time, NULL);
			if (sleepsleep(phil, phil->sim->time_to_eat * 1000) == FAIL)
				return (NULL);
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
			if (read_sim_status(phil->sim) == true)
				log_action(phil->sim, phil->num, log_sleep);
			else
				return (NULL);
			phil->state = EATING;
		}
		if (phil->state == EATING)
		{
			phil->state = SLEEPING;
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
				return (NULL);
			}
			if (phil->sim->time_to_sleep * 1000 + get_mtime(phil->phil_eat_time)
				>= phil->sim->time_to_die * 1000)
			{
				phil->state = DEAD;
				if (sleepsleep(phil, (phil->sim->time_to_die * 1000 - get_mtime(phil->phil_eat_time))) == FAIL)
					return (NULL);
				pthread_mutex_lock(&phil->sim->status_mutex);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					pthread_mutex_unlock(&phil->sim->status_mutex);
					pthread_mutex_lock(&phil->sim->logging_mutex);
					printf("%-4lu %-3u has died\n",
						get_time(phil->phil_eat_time), phil->num);
					pthread_mutex_unlock(&phil->sim->logging_mutex);
				}
				else
					pthread_mutex_unlock(&phil->sim->status_mutex);
				return (NULL);
			}
			else
			{
				if (sleepsleep(phil, phil->sim->time_to_sleep * 1000) == FAIL)
					return (NULL);
			}
			if (read_sim_status(phil->sim) == true)
				log_action(phil->sim, phil->num, log_think);
			else
				return (NULL);
		}
		if (phil->state == SLEEPING)
		{
			phil->state = THINKING;
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
				return (NULL);
			}
		}
		if (phil->state == DEAD)
			return (NULL);
	}
	return (NULL);
}

unsigned int	read_num_eats(t_phil *phil)
{
	unsigned int	num_eats;

	pthread_mutex_lock(&phil->num_eats_mutex);
	num_eats = phil->num_eats;
	pthread_mutex_unlock(&phil->num_eats_mutex);
	return (num_eats);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->num_phils)
	{
		pthread_mutex_destroy(&sim->fork_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->logging_mutex);
	pthread_mutex_destroy(&sim->status_mutex);
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	ft_free(&sim->fork_mutexes);
	ft_free(&sim->fork_takers);
	ft_free(&sim);
}
