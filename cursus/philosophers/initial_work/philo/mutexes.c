/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:32:16 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/08 09:53:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Creates a mutex and handles errors
void	create_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != SUCCESS)
	{
		write_to_stderror("Failed to create mutex\n");
	}
}

// Frees a mutex and handles errors
void	free_mutex(pthread_mutex_t *mutex)
{
	// printf("%d\n", pthread_mutex_lock(mutex));
	if (pthread_mutex_destroy(mutex) != SUCCESS)
	{
		write_to_stderror("Failed to free mutex\n");
	}
}

// Locks a mutex and handles errors
void	lock_mutex(pthread_mutex_t *mutex)
{
	// printf("%d\n", pthread_mutex_lock(mutex));
	if (pthread_mutex_lock(mutex) != SUCCESS)
	{
		// perror(NULL);
		write_to_stderror("Failed to lock mutex\n");
	}
}

// Unlocks a mutex and handles errors
void	unlock_mutex(pthread_mutex_t *mutex)
{
	// printf("%d\n", pthread_mutex_unlock(mutex));
	if (pthread_mutex_unlock(mutex) != SUCCESS)
	{
		// perror(NULL);
		write_to_stderror("Failed to unlock mutex\n");
	}
}
