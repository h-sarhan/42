/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/06 22:14:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a simulation struct
t_sim	*create_simulation(void)
{
	t_sim	*sim;
	bool	success;

	sim = ft_calloc(1, sizeof(t_sim));
	if (sim == NULL)
	{
		write_to_stderror("Failed to allocate memory\n", NULL);
		return (NULL);
	}
	sim->start_time = ft_calloc(1, sizeof(t_timeval));
	if (sim->start_time == NULL)
	{
		write_to_stderror("Failed to allocate memory\n", NULL);
		return (NULL);
	}
	get_start_time(sim->start_time);
	create_mutex(&sim->logging_mutex, &success);
	create_mutex(&sim->status_mutex, &success);
	if (sim->start_time == NULL || success == false)
	{
		free_sim(sim);
		return (NULL);
	}
	sim->status = true;
	return (sim);
}

bool	read_sim_status(t_sim *sim, bool *success)
{
	bool	status;

	lock_mutex(&sim->status_mutex, success);
	status = sim->status;
	unlock_mutex(&sim->status_mutex, success);
	return (status);
}

void	set_sim_status(t_sim *sim, const bool status, bool *success)
{
	lock_mutex(&sim->status_mutex, success);
	sim->status = status;
	unlock_mutex(&sim->status_mutex, success);
}

// Starts the eat->think->sleep cycle of a philosopher
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
	left_held = read_fork_status(phil->sim, left, &success);
	if (left == right)
		right_held = true;
	else
		right_held = read_fork_status(phil->sim, right, &success);
	while (1)
	{
		if (phil->state == THINKING)
		{
			success = true;
			while ((left_held == true || right_held == true))	
			{
				left_held = read_fork_status(phil->sim, left, &success);
				if (left == right)
					right_held = true;
				else
					right_held = read_fork_status(phil->sim, right, &success);
				if (get_micro_time(phil->phil_eat_time, &success) >= phil->sim->time_to_die * 1000)
				{
					// printf("%d DIED WHILE WATING FOR FORK\n", phil->num);
					phil->state = DEAD;
					lock_mutex(&phil->sim->status_mutex, &success);
					if (phil->sim->status == true)
					{
						phil->sim->status = false;
						unlock_mutex(&phil->sim->status_mutex, &success);
						log_action(phil->sim, phil->num, &success, log_death);
					}
					else
						unlock_mutex(&phil->sim->status_mutex, &success);
					return (NULL);
				}
			}
			if (read_sim_status(phil->sim, &success) == false)
				return (NULL);
			set_fork_status(phil->sim, left, true, &success);
			set_fork_status(phil->sim, right, true, &success);
			time = get_time(phil->sim->start_time, &success);
			lock_mutex(&phil->sim->logging_mutex, &success);
			log_fork(&time, phil->num, &success);
			log_fork(&time, phil->num, &success);
			log_eat(&time, phil->num, &success);
			unlock_mutex(&phil->sim->logging_mutex, &success);
			get_start_time(phil->phil_eat_time);
			sleepsleep(phil->sim->time_to_eat * 1000);
			if (read_sim_status(phil->sim, &success) == true)
				log_action(phil->sim, phil->num, &success, log_sleep);
			else
				return (NULL);
			phil->state = EATING;
		}
		if (phil->state == EATING)
		{
			phil->state = SLEEPING;
			if (get_micro_time(phil->phil_eat_time, &success) >= phil->sim->time_to_die * 1000)
			{
				printf("%d DIED AFTER EATING\n", phil->num);

				phil->state = DEAD;
				lock_mutex(&phil->sim->status_mutex, &success);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex, &success);
					// set_sim_status(phil->sim, false, &success);
					log_action(phil->sim, phil->num, &success, log_death);
				}
				else
					unlock_mutex(&phil->sim->status_mutex, &success);
				return (NULL);
			}
			set_fork_status(phil->sim, left, false, &success);
			set_fork_status(phil->sim, right, false, &success);
			time = phil->sim->time_to_sleep * 1000 + get_micro_time(phil->phil_eat_time, &success);
			if (time >= phil->sim->time_to_die * 1000)
			{
				phil->state = DEAD;
				printf("%d GO HERE AND SLEEP %lums\n", phil->num, (phil->sim->time_to_die - phil->sim->time_to_sleep));
				sleepsleep((phil->sim->time_to_die * 1000 - get_micro_time(phil->phil_eat_time, &success)));
				
				lock_mutex(&phil->sim->status_mutex, &success);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex, &success);
					lock_mutex(&phil->sim->logging_mutex, &success);
					printf("%-4lu %-3u has died\n", get_time(phil->phil_eat_time, &success), phil->num);
					unlock_mutex(&phil->sim->logging_mutex, &success);
				}
				else
					unlock_mutex(&phil->sim->status_mutex, &success);
				return (NULL);
			}
			else
				sleepsleep(phil->sim->time_to_sleep * 1000);
			if (read_sim_status(phil->sim, &success) == true)
				log_action(phil->sim, phil->num, &success, log_think);
			else
				return (NULL);
		}
		if (phil->state == SLEEPING)
		{
			phil->state = THINKING;
			if (get_micro_time(phil->phil_eat_time, &success) >= phil->sim->time_to_die * 1000)
			{
				phil->state = DEAD;
				printf("%d DIED AFTER SLEEPING\n", phil->num);
				
				lock_mutex(&phil->sim->status_mutex, &success);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex, &success);
					log_action(phil->sim, phil->num, &success, log_death);
				}
				else
					unlock_mutex(&phil->sim->status_mutex, &success);
				return (NULL);
			}
		}
		if (phil->state == DEAD)
			return (NULL);
	}
	return (NULL);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	ft_free(&sim->fork_mutexes);
	ft_free(&sim);
}
