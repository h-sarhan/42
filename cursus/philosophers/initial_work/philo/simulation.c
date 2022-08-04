/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 16:59:07 by hsarhan          ###   ########.fr       */
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
	sim->start_time = get_start_time();
	sim->logging_mutex = create_mutex(&success);
	if (sim->start_time == NULL || success == false)
	{
		free_sim(sim);
		return (NULL);
	}
	return (sim);
}

// Starts the eat->think->sleep cycle of a philosopher
void	*run_sim(void *phil_ptr)
{
	unsigned int	left;
	unsigned int	right;
	bool			success;
	t_phil			*phil;
	t_timeval		*phil_eat_time;
	bool			left_held;
	bool			right_held;

	phil_eat_time = get_start_time();
	phil = (t_phil *) phil_ptr;
	while (1)
	{
		// if (phil->state == THINKING)
		if (read_phil_state(phil, &success) == THINKING)
		{
			left = phil->num;
			right = phil->num + 1;
			success = true;
			if (phil->num == phil->sim->num_phils)
				right = 1;
			// left_held = false;
			// right_held = false;
			lock_mutex(&phil->sim->fork_mutexes[left], &success);
			left_held = phil->sim->forks[left];
			unlock_mutex(&phil->sim->fork_mutexes[left], &success);
			lock_mutex(&phil->sim->fork_mutexes[right], &success);
			right_held = phil->sim->forks[right];
			unlock_mutex(&phil->sim->fork_mutexes[right], &success);
			while (left_held == true || right_held == true)	
			{
				lock_mutex(&phil->sim->fork_mutexes[left], &success);
				left_held = phil->sim->forks[left];
				unlock_mutex(&phil->sim->fork_mutexes[left], &success);
				lock_mutex(&phil->sim->fork_mutexes[right], &success);
				right_held = phil->sim->forks[right];
				unlock_mutex(&phil->sim->fork_mutexes[right], &success);
				if (get_time(phil_eat_time, &success) >= phil->sim->time_to_die)
				{
					// phil->state = DEAD;
					set_phil_state(phil, DEAD, &success);
					log_action(phil->sim, phil->num, &success, log_death);
					return (NULL);
				}
			}
			set_fork_status(phil->sim, left, true, &success);
			log_action(phil->sim, phil->num, &success, log_fork);
			set_fork_status(phil->sim, right, true, &success);
			log_action(phil->sim, phil->num, &success, log_fork);
			// phil->state = EATING;
			set_phil_state(phil, EATING, &success);
			log_action(phil->sim, phil->num, &success, log_eat);
			usleep(phil->sim->time_to_eat * 1000);
			phil_eat_time = get_start_time();
			set_fork_status(phil->sim, left, false, &success);
			set_fork_status(phil->sim, right, false, &success);
		}
		// if (phil->state == EATING)
		if (read_phil_state(phil, &success) == EATING)
		{
			// phil->state = SLEEPING;
			set_phil_state(phil, SLEEPING, &success);
			log_action(phil->sim, phil->num, &success, log_sleep);
			usleep(phil->sim->time_to_sleep * 1000);
			if (get_time(phil_eat_time, &success) >= phil->sim->time_to_die)
			{
				// phil->state = DEAD;
				set_phil_state(phil, DEAD, &success);
				log_action(phil->sim, phil->num, &success, log_death);
				return (NULL);
			}
		}
		// if (phil->state == SLEEPING)
		if (read_phil_state(phil, &success) == SLEEPING)
		{
			set_phil_state(phil, THINKING, &success);
			// phil->state = THINKING;
			log_action(phil->sim, phil->num, &success, log_think);
		}
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
