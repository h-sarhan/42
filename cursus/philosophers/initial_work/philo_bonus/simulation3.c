/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:41:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/03 22:12:21 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think_phase(t_phil *phil)
{
	phil->state = THINKING;
	if (log_action(phil->sim, phil->num, log_think) == false)
		return (END);
	if (check_time_since_eat(phil) == END)
		return (END);
	return (CONTINUE);
}

int	check_time_since_eat(t_phil *phil)
{
	if (get_mtime(phil->phil_eat_time) >= phil->sim->time_to_die * 1000)
	{
		// sem_wait(phil->sim->sems->status);
		phil->state = DEAD;
		log_action(phil->sim, phil->num, log_death);
		sem_wait(phil->sim->sems->logging);
		// sem_wait(phil->sim->sems->status);
		// kill_philosophers(phil);
		exit(0);
		// sem_wait(phil->sim->sems->status);
		// if (phil->sim->status == true)
		// {
		// 	phil->sim->status = false;
		// 	sem_post(phil->sim->sems->status);
		// 		return (END);
		// }
		// else
		// 	sem_post(phil->sim->sems->status);
		return (END);
	}
	return (CONTINUE);
}

// void	kill_philosophers(t_phil *phil)
// {
// 	size_t	i;

// 	i = 0;
// 	printf("KILLING\n");
// 	while (i < phil->sim->num_phils)
// 	{
// 		if (phil->sim->philosopher_pids[i] != 0)
// 		{
// 			kill(phil->sim->philosopher_pids[i], SIGKILL);
// 		}
// 		i++;
// 	}
// 	exit(0);
// }

int	sleep_phase(t_phil *phil)
{
	if (log_action(phil->sim, phil->num, log_sleep) == false)
		return (END);
	if (phil->sim->time_to_sleep * 1000 + get_mtime(phil->phil_eat_time)
		>= phil->sim->time_to_die * 1000)
	{
		if (phil->sim->time_to_die * 1000 > get_mtime(phil->phil_eat_time)
			&& sleepsleep(phil, (phil->sim->time_to_die * 1000 - \
				get_mtime(phil->phil_eat_time))) == FAIL)
			return (END);
		log_action(phil->sim, phil->num, log_death);
		// sem_wait(phil->sim->sems->status);
		sem_wait(phil->sim->sems->logging);
		exit(0);
		// kill_philosophers(phil);
		// sem_wait(phil->sim->sems->status);
		// if (phil->sim->status == true)
		// {
		// 	phil->sim->status = false;
		// 	sem_post(phil->sim->sems->status);
		// 	if (log_action(phil->sim, phil->num, log_death) == false)
		// 		return (END);
		// }
		// else
		// 	sem_post(phil->sim->sems->status);
		return (END);
	}
	if (sleepsleep(phil, phil->sim->time_to_sleep * 1000) == FAIL
		|| check_time_since_eat(phil) == END)
		return (END);
	return (CONTINUE);
}



void	put_back_fork(t_phil *phil)
{
	sem_post(phil->sim->sems->num_forks);
}

void	pick_up_fork(t_phil *phil)
{
	sem_wait(phil->sim->sems->num_forks);
}
