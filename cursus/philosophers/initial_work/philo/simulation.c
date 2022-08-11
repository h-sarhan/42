/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/11 18:13:39 by hsarhan          ###   ########.fr       */
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
	// if (left == right)
	// 	right_held = true;
	// else
		right_held = true;
	while (1)
	{
		if (phil->state == THINKING)
		{
			success = true;
			while ((left_held == true || right_held == true))	
			{
				left_held = read_fork_status(phil->sim, left);
				if (left == right)
					right_held = true;
				else
					right_held = read_fork_status(phil->sim, right);
				if (get_micro_time(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
				{
					// printf("%d DIED WHILE WATING FOR FORK\n", phil->num);
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
			}
			// lock_mutex(&phil->sim->logging_mutex);
			// printf("fork %d and fork %d have been taken by philosopher %d\n", left, right, phil->num);
			// unlock_mutex(&phil->sim->logging_mutex);
			// f | f | f
			set_fork_status(phil->sim, left, true);
			set_fork_status(phil->sim, right, true);
			// if (read_sim_status(phil->sim) == false)
			// 	return (NULL);
			time = get_time(phil->sim->start_time);
			lock_mutex(&phil->sim->logging_mutex);
			log_fork(&time, phil->num);
			log_fork(&time, phil->num);
			log_eat(&time, phil->num);
			unlock_mutex(&phil->sim->logging_mutex);
			get_start_time(phil->phil_eat_time);
			sleepsleep(phil->sim->time_to_eat * 1000);
			set_fork_status(phil->sim, left, false);
			set_fork_status(phil->sim, right, false);
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
				// printf("%d DIED AFTER EATING\n", phil->num);

				phil->state = DEAD;
				lock_mutex(&phil->sim->status_mutex);
				if (phil->sim->status == true)
				{
					phil->sim->status = false;
					unlock_mutex(&phil->sim->status_mutex);
					// set_sim_status(phil->sim, false);
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
				// printf("%d GO HERE AND SLEEP %lums\n", phil->num, (phil->sim->time_to_die - phil->sim->time_to_sleep));
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
				printf("%d DIED AFTER SLEEPING\n", phil->num);
				
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
