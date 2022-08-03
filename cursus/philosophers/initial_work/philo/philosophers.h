/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:29:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 15:04:56 by hsarhan          ###   ########.fr       */
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
# include <string.h>
# include <stdint.h>

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
typedef struct timeval		t_timeval;
typedef 					void (*log_func)(const t_sim *sim,
								const size_t phil_num, bool *success);
// Simulation Struct
struct s_sim
{
	unsigned int	num_phils;
	t_time_ms		time_to_die;
	t_time_ms		time_to_eat;
	t_time_ms		time_to_sleep;
	unsigned int	min_eats;
	t_timeval		*start_time;
	bool			*forks;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	logging_mutex;
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
	// pthread_t		thread;
	t_phil_state	state;
	unsigned int	num;
	t_sim			*sim;
};

// Philosopher Functions
t_phil			**create_philosophers(t_sim *sim);
void			free_philosophers(t_phil **phils);
// void			*run_simulation();

// Simulation Functions
t_sim			*create_simulation(void);
void			free_sim(t_sim *sim);
void			*run_sim(void *phil);
void			create_forks(t_sim *sim, bool *success);

// Utils
size_t			ft_strlen(const char *str);
void			ft_free(void *memory);
void			*ft_calloc(size_t count, size_t size);

// Error Handling
void			write_to_stderror(const char *msg, bool *success);

// Time
t_timeval		*get_start_time(void);
t_time_ms		get_time(const t_sim *sim, bool *success);

// Threading Functions
pthread_t		create_thread(void *(*f)(void *), void *arg, bool *success);
void			detach_thread(const pthread_t *thread, bool *success);
void			join_thread(const pthread_t *thread, bool *success, void **ret);

// Logging Functions
void			log_fork(const t_sim *sim, const size_t phil_num, bool *succ);
void			log_eat(const t_sim *sim, const size_t phil_num, bool *succ);
void			log_sleep(const t_sim *sim, const size_t phil_num, bool *succ);
void			log_think(const t_sim *sim, const size_t phil_num, bool *succ);
void			log_death(const t_sim *sim, const size_t phil_num, bool *succ);
void			log_action(t_sim *sim, const size_t phil_num, bool *succ, log_func f);

// Parsing
long			atoui(const char *str);
void			parse_args(t_sim *sim, const int argc, char **argv, bool *succ);

// Mutexes
pthread_mutex_t	create_mutex(bool *success);
void			free_mutex(pthread_mutex_t *mutex, bool *success);
void			lock_mutex(pthread_mutex_t *mutex, bool *success);
void			unlock_mutex(pthread_mutex_t *mutex, bool *success);

// Fork status
bool			read_fork_status(const t_sim *sim, const unsigned int fork_idx,
					bool *succ);
void			set_fork_status(t_sim *sim, const unsigned int fork_idx,
					const bool value, bool *success);

#endif