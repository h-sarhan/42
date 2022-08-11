/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/11 21:00:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_sim *create_simulation(void)
{
	t_sim *sim;

	sim = ft_calloc(1, sizeof(t_sim));
	if (sim == NULL)
	{
		write_to_stderror("Failed to allocate memory\n");
		return (NULL);
	}
	sim->start_time = ft_calloc(1, sizeof(t_timeval));
	if (sim->start_time == NULL)
	{
		write_to_stderror("Failed to allocate memory\n");
		return (NULL);
	}
	get_start_time(sim->start_time);
	create_mutex(&sim->logging_mutex);
	create_mutex(&sim->status_mutex);
	if (sim->start_time == NULL)
	{
		free_sim(sim);
		return (NULL);
	}
	sim->status = true;
	return (sim);
}

bool read_sim_status(t_sim *sim)
{
	bool status;

	lock_mutex(&sim->status_mutex);
	status = sim->status;
	unlock_mutex(&sim->status_mutex);
	return (status);
}

void set_sim_status(t_sim *sim, const bool status)
{
	lock_mutex(&sim->status_mutex);
	sim->status = status;
	unlock_mutex(&sim->status_mutex);
}

void	*run_sim(void *phil_ptr)
{
	unsigned int	left;
	unsigned int	right;
	bool			success;
	t_phil			*phil;
	bool			left_held;
	bool			right_held;
	t_time_ms		time;

	phil = (t_phil *) phil_ptr;
	get_start_time(phil->phil_eat_time);
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
			success = true;
			lock_mutex(&phil->sim->fork_mutexes[left]);
			if (left != right)
				lock_mutex(&phil->sim->fork_mutexes[right]);
			while ((left_held == true || right_held == true))	
			{
				left_held = phil->sim->forks[left];
				if (left == right)
					right_held = true;
				else
				{
					right_held = phil->sim->forks[right];
				}
				if (get_micro_time(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
				{
					unlock_mutex(&phil->sim->fork_mutexes[left]);
					if (left != right)
						unlock_mutex(&phil->sim->fork_mutexes[right]);
					phil->state = DEAD;
					lock_mutex(&phil->sim->status_mutex);
					if (phil->sim->status == true)
					{
						phil->sim->status = false;
						unlock_mutex(&phil->sim->status_mutex);
						log_action(phil->sim, phil->num, log_death);
					}
					else
						unlock_mutex(&phil->sim->status_mutex);
					return (NULL);
				}
				if (left_held == false || right_held == false)
				{
					unlock_mutex(&phil->sim->fork_mutexes[left]);
					if (left != right)
						unlock_mutex(&phil->sim->fork_mutexes[right]);
					lock_mutex(&phil->sim->fork_mutexes[left]);
					if (left != right)
						lock_mutex(&phil->sim->fork_mutexes[right]);
				}
			}
			phil->sim->forks[left] = true;
			unlock_mutex(&phil->sim->fork_mutexes[left]);
			phil->sim->forks[right] = true;
			unlock_mutex(&phil->sim->fork_mutexes[right]);

			time = get_time(phil->sim->start_time);
			lock_mutex(&phil->sim->logging_mutex);
			log_fork(&time, phil->num);
			log_fork(&time, phil->num);
			log_eat(&time, phil->num);
			unlock_mutex(&phil->sim->logging_mutex);

			lock_mutex(&phil->num_eats_mutex);
			phil->num_eats++;
			unlock_mutex(&phil->num_eats_mutex);

			get_start_time(phil->phil_eat_time);
			sleepsleep(phil->sim->time_to_eat * 1000);

			lock_mutex(&phil->sim->fork_mutexes[left]);
			phil->sim->forks[left] = false;
			unlock_mutex(&phil->sim->fork_mutexes[left]);
			lock_mutex(&phil->sim->fork_mutexes[right]);
			phil->sim->forks[right] = false;
			unlock_mutex(&phil->sim->fork_mutexes[right]);
			if (read_sim_status(phil->sim) == true)
				log_action(phil->sim, phil->num, log_sleep);
			else
				return (NULL);
			phil->state = EATING;
		}
		if (phil->state == EATING)
		{
			phil->state = SLEEPING;
			if (get_micro_time(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
			{
				phil->state = DEAD;
				lock_mutex(&phil->sim->status_mutex);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex);
					log_action(phil->sim, phil->num, log_death);
				}
				else
					unlock_mutex(&phil->sim->status_mutex);
				return (NULL);
			}
			time = phil->sim->time_to_sleep * 1000 + get_micro_time(phil->phil_eat_time);
			if (time >= phil->sim->time_to_die * 1000)
			{
				phil->state = DEAD;
				sleepsleep((phil->sim->time_to_die * 1000 - get_micro_time(phil->phil_eat_time)));
				
				lock_mutex(&phil->sim->status_mutex);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex);
					lock_mutex(&phil->sim->logging_mutex);
					printf("%-4lu %-3u has died\n", get_time(phil->phil_eat_time), phil->num);
					unlock_mutex(&phil->sim->logging_mutex);
				}
				else
					unlock_mutex(&phil->sim->status_mutex);
				return (NULL);
			}
			else
				sleepsleep(phil->sim->time_to_sleep * 1000);
			if (read_sim_status(phil->sim) == true)
				log_action(phil->sim, phil->num, log_think);
			else
				return (NULL);
		}
		if (phil->state == SLEEPING)
		{
			phil->state = THINKING;
			if (get_micro_time(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
			{
				phil->state = DEAD;
				lock_mutex(&phil->sim->logging_mutex);
				printf("%d DIED AFTER SLEEPING\n", phil->num);
				unlock_mutex(&phil->sim->logging_mutex);
				
				lock_mutex(&phil->sim->status_mutex);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex);
					log_action(phil->sim, phil->num, log_death);
				}
				else
					unlock_mutex(&phil->sim->status_mutex);
				return (NULL);
			}
		}
		if (phil->state == DEAD)
			return (NULL);
	}
	return (NULL);
}


// Frees a simulation struct
void free_sim(t_sim *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	ft_free(&sim->fork_mutexes);
	ft_free(&sim);
}
