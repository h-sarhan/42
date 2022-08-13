/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:55:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/13 11:23:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Wrapper function around pthread_create that handles errors
void	create_thread(pthread_t *thread, void *(*f)(void *), void *arg)
{
	if (pthread_create(thread, NULL, f, arg) != SUCCESS)
	{
		write_to_stderror("Failed to create thread\n");
		return ;
	}
	return ;
}

// Wrapper function around pthread_join that handles errors
void	join_thread(const pthread_t *thread, void **ret)
{
	if (pthread_join(*thread, ret) != SUCCESS)
	{
		write_to_stderror("Failed to join thread\n");
		return ;
	}
}
