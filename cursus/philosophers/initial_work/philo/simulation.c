/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:44:51 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 15:05:34 by hsarhan          ###   ########.fr       */
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
	bool			fork_left_held;
	bool			fork_right_held;
	
	phil = (t_phil *) phil_ptr;
	left = phil->num;
	right = phil->num + 1;
	success = true;
	if (phil->num == phil->sim->num_phils)
		right = 1;
	
	fork_left_held = read_fork_status(phil->sim, left, &success);
	fork_right_held = read_fork_status(phil->sim, right, &success);

	if (fork_left_held == false && fork_right_held == false)
	{
		set_fork_status(phil->sim, left, true, &success);
		set_fork_status(phil->sim, right, true, &success);
		usleep(phil->sim->time_to_eat * 1000);
		log_action(phil->sim, phil->num, &success, log_eat);
		set_fork_status(phil->sim, left, false, &success);
		set_fork_status(phil->sim, right, false, &success);
	}
	return (NULL);
}

// Frees a simulation struct
void	free_sim(t_sim *sim)
{
	ft_free(&sim->start_time);
	ft_free(&sim->forks);
	ft_free(&sim);
}
