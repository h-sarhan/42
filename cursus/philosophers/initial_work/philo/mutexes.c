/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 20:32:16 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/02 10:32:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	create_mutex(bool *success)
{
	pthread_mutex_t	mutex;

	if (pthread_mutex_init(&mutex, NULL) != SUCCESS)
	{
		write_to_stderror("Failed to create mutex\n", NULL);
		*success = false;
		return (mutex);
	}
	*success = true;
	return (mutex);
}

void	free_mutex(pthread_mutex_t mutex, bool *success)
{
	if (pthread_mutex_destroy(&mutex) != SUCCESS)
	{
		write_to_stderror("Failed to free mutex\n", NULL);
		*success = false;
	}
	*success = true;
}

void	lock_mutex(pthread_mutex_t mutex, bool *success)
{
	if (pthread_mutex_lock(&mutex) != SUCCESS)
	{
		write_to_stderror("Failed to lock mutex\n", NULL);
		*success = false;
	}
	*success = true;
}

void	unlock_mutex(pthread_mutex_t mutex, bool *success)
{
	if (pthread_mutex_lock(&mutex) != SUCCESS)
	{
		write_to_stderror("Failed to unlock mutex\n", NULL);
		*success = false;
	}
	*success = true;
}
