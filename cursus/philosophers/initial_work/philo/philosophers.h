/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:29:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 19:08:54 by hsarhan          ###   ########.fr       */
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
typedef struct s_sim		t_sim;
typedef struct s_phil		t_phil;
typedef unsigned long		t_time_ms;
typedef enum e_phil_state	t_phil_state;

// Simulation Struct
struct s_sim
{
	unsigned int	num_phils;
	t_time_ms		time_to_die;
	t_time_ms		time_to_eat;
	t_time_ms		time_to_sleep;
	unsigned int	min_eats;
	struct timeval	*start_time;
	t_phil			*phils;
	bool			*forks;
};

// Philosopher States
enum e_phil_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

// Philosopher Struct
struct s_phil
{
	pthread_t		thread;
	t_phil_state	state;
	// bool			holding_lfork;
	// bool			holding_rfork;
};

// Philosopher Functions
void					create_philosophers(t_sim *sim, bool *success);

// Simulation Functions
t_sim					*create_simulation(void);
void					free_sim(t_sim *sim);

// Utils
size_t					ft_strlen(const char *str);
void					ft_free(void *memory);

// Error Handling
void					write_to_stderror(const char *msg, bool *success);

// Time
struct timeval			*get_start_time(void);
t_time_ms				get_time(const t_sim *sim, bool *success);

// Threading Functions
pthread_t				create_thread(void *(*f)(void *), void *arg,
							bool *success);
void					detach_thread(const pthread_t *thread, bool *success);
void					join_thread(const pthread_t *thread, bool *success);

// Logging Functions
void					log_fork(const t_sim *sim, const size_t phil_num,
							bool *success);
void					log_eat(const t_sim *sim, const size_t phil_num,
							bool *success);
void					log_sleep(const t_sim *sim, const size_t phil_num,
							bool *success);
void					log_think(const t_sim *sim, const size_t phil_num,
							bool *success);
void					log_death(const t_sim *sim, const size_t phil_num,
							bool *success);

// Parsing
long					ft_atol(const char *str);
void					parse_args(t_sim *sim, const int argc, char **argv,
							bool *success);
#endif