/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:55:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 20:28:23 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Wrapper function around pthread_create that handles errors
pthread_t	create_thread(void *(*f)(void *), void *arg, bool *success)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, f, arg) != SUCCESS)
	{
		write_to_stderror("Failed to create thread\n", NULL);
		*success = false;
		return (THREAD_FAILURE);
	}
	*success = true;
	return (thread);
}

// Wrapper function around pthread_detach that handles errors
void	detach_thread(const pthread_t *thread, bool *success)
{
	if (pthread_detach(*thread) != SUCCESS)
	{
		write_to_stderror("Failed to detach thread\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}

// Wrapper function around pthread_join that handles errors
void	join_thread(const pthread_t *thread, bool *success, void **ret)
{
	if (pthread_join(*thread, ret) != SUCCESS)
	{
		write_to_stderror("Failed to join thread\n", NULL);
		*success = false;
		return ;
	}
	*success = true;
}
