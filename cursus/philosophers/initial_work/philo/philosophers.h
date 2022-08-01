/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:29:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 13:55:03 by hsarhan          ###   ########.fr       */
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
struct s_sim
{
	struct timeval	*start_time;
};
typedef struct s_sim	t_sim;

// Simulation functions
t_sim					*create_simulation(void);
void					free_sim(t_sim *sim);

// Utils
size_t					ft_strlen(const char *str);
void					ft_free(void *memory);

// Error Handling
void					write_to_stderror(const char *msg);

// Time
typedef unsigned long	t_time_ms;
struct timeval			*get_start_time(void);
t_time_ms				get_time(t_sim *sim);

// Threading functions
pthread_t				create_thread(t_sim *sim, void *(*f)(void *),
							void *arg);
void					detach_thread(t_sim *sim, const pthread_t *thread);
void					join_thread(t_sim *sim, const pthread_t *thread);

// Logging functions
void					log_fork(t_sim *sim, size_t phil_num);
void					log_eat(t_sim *sim, size_t phil_num);
void					log_eat(t_sim *sim, size_t phil_num);
void					log_think(t_sim *sim, size_t phil_num);
void					log_death(t_sim *sim, size_t phil_num);

#endif