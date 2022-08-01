/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:29:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 15:58:27 by hsarhan          ###   ########.fr       */
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
# include <limits.h>

// Constants
# define FAIL -1
# define SUCCESS 0
# define TIME_FAILURE 0
# define THREAD_FAILURE 0

// Typedefs
typedef struct s_sim	t_sim;
typedef unsigned long	t_time_ms;

// Simulation struct
struct s_sim
{
	unsigned int			num_phils;
	t_time_ms				time_to_die;
	t_time_ms				time_to_eat;
	t_time_ms				time_to_sleep;
	unsigned int			min_eats;
	struct timeval			*start_time;
};

// Simulation functions
t_sim					*create_simulation(void);
void					free_sim(t_sim *sim);

// Utils
size_t					ft_strlen(const char *str);
void					ft_free(void *memory);

// Error Handling
void					write_to_stderror(const char *msg, bool *success);

// Time
struct timeval			*get_start_time(void);
t_time_ms				get_time(t_sim *sim, bool *success);

// Threading functions
pthread_t				create_thread(void *(*f)(void *), void *arg,
							bool *success);
void					detach_thread(const pthread_t *thread, bool *success);
void					join_thread(const pthread_t *thread, bool *success);

// Logging functions
void					log_fork(t_sim *sim, size_t phil_num, bool *success);
void					log_eat(t_sim *sim, size_t phil_num, bool *success);
void					log_sleep(t_sim *sim, size_t phil_num, bool *success);
void					log_think(t_sim *sim, size_t phil_num, bool *success);
void					log_death(t_sim *sim, size_t phil_num, bool *success);

// Parsing
long					ft_atol(const char *str);
void					parse_args(t_sim *sim, const int argc, char **argv,
							bool *success);
#endif