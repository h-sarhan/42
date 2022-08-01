/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:29:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 13:18:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>

// Constants
# define FAIL -1
# define SUCCESS 0

// Simulation struct
struct s_simulation
{
	struct timeval	*start_time;
};
typedef struct s_simulation	t_simulation;

// Simulation functions
t_simulation				*create_simulation(void);
void						free_sim(t_simulation *sim);

// Utils
size_t						ft_strlen(const char *str);
void						ft_free(void *memory);

// Error Handling
void						write_to_stderror(const char *msg);

// Time
typedef unsigned long		t_time_ms;
struct timeval				*get_start_time(void);
t_time_ms					get_time(t_simulation *sim);

// Threading function
pthread_t					create_thread(t_simulation *sim, void *(*f)(void *),
								void *arg);

#endif