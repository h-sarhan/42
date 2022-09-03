/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:29:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/03 22:40:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes
# include <sys/time.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <stdint.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

// Constants
# define FAIL -1
# define SUCCESS 0
# define TIME_FAILURE 0
# define CONTINUE 1
# define END 0

// Typedefs
typedef struct s_sim		t_sim;
typedef struct s_phil		t_phil;
typedef unsigned long		t_time_ms;
typedef enum e_phil_state	t_phil_state;
typedef struct timeval		t_timeval;
typedef void				(*t_log_func)(const t_time_ms *time,
								const size_t phil_num);
typedef struct s_sems		t_sems;

struct s_sems
{
	sem_t	*num_forks;
	sem_t	*logging;
	sem_t	**num_eats;
};

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
	unsigned int	*fork_takers;
	bool			status;
	int				*philosopher_pids;
	t_sems			*sems;
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
	t_phil_state	state;
	unsigned int	num;
	// pthread_mutex_t	num_eats_mutex;
	unsigned int	num_eats;
	t_sim			*sim;
	t_timeval		*phil_eat_time;
};

// Philosopher Functions
t_phil			**create_philosophers(t_sim *sim);
void			free_philosophers(t_phil **phils);

// Simulation Functions
t_sim			*create_simulation(void);
void			free_sim(t_sim *sim);
void			*run_sim(void *phil);
void			create_forks(t_sim *sim);
bool			read_sim_status(t_sim *sim);
unsigned int	read_num_eats(t_phil *phil);
int				think_phase(t_phil *phil);
int				check_time_since_eat(t_phil *phil);
int				sleep_phase(t_phil *phil);
int				eating_phase(t_phil *phil);
void			pick_up_fork(t_phil *phil);
void			put_back_fork(t_phil *phil);
void			kill_philosophers(t_sim *sim);
void			check_sim_status(t_phil *phil);
// Utils
size_t			ft_strlen(const char *str);
void			ft_free(void *memory);
void			*ft_calloc(size_t count, size_t size);
int				sleepsleep(t_phil *phil, t_time_ms sleep_time);

// Time
t_time_ms		get_time(const t_timeval *sim);
t_time_ms		get_mtime(const t_timeval *start_time);

// Logging Functions
void			log_eat(const t_time_ms *time, const size_t phil_num);
void			log_sleep(const t_time_ms *time, const size_t phil_num);
void			log_think(const t_time_ms *time, const size_t phil_num);
void			log_death(const t_time_ms *time, const size_t phil_num);
bool			log_action(t_sim *sim, const size_t phil_num, t_log_func f);
void	log_fork(const t_time_ms *time, const size_t phil_num);


// Parsing
long			atoui(const char *str);
void			parse_args(t_sim *sim, const int argc, char **argv,
					bool *success);

#endif