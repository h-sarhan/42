/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:55:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 13:55:30 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Wrapper function around pthread_create that handles errors
pthread_t	create_thread(t_sim *sim, void *(*f)(void *), void *arg)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, f, arg) != SUCCESS)
	{
		write_to_stderror("Failed to create thread\n");
		free_sim(sim);
		exit(EXIT_FAILURE);
	}
	return (thread);
}

// Wrapper function around pthread_detach that handles errors
void	detach_thread(t_sim *sim, const pthread_t *thread)
{
	if (pthread_detach(*thread) != SUCCESS)
	{
		write_to_stderror("Failed to detach thread\n");
		free_sim(sim);
		exit(EXIT_FAILURE);
	}
}

// Wrapper function around pthread_join that handles errors
void	join_thread(t_sim *sim, const pthread_t *thread)
{
	if (pthread_join(*thread, NULL) != SUCCESS)
	{
		write_to_stderror("Failed to join thread\n");
		free_sim(sim);
		exit(EXIT_FAILURE);
	}
}
