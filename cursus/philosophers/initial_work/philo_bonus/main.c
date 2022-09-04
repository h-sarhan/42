/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 08:40:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Tests: 
// ? valgrind --tool=helgrind --history-level=none  ./philo_bonus 5 800 200 200 7

// * ./philo_bonus 1 800 200 200: Should not eat and die
// * ./philo_bonus 5 800 200 200 7: No one should die
// * ./philo_bonus 4 410 200 200: No one should die
// * ./philo_bonus 4 310 200 100: A philosopher should die
// Philosophers

// * ./philo_bonus 3 1000 500 600
// * ./philo_bonus 5 200 100 60
// * ./philo_bonus 4 500 400 300
// * ./philo_bonus 3 700 200 200 Philosophers shouldnt die here
// * ./philo_bonus 199 800 200 100

static void	*check_for_min_eats(void *sim_ptr)
{
	t_sim	*sim;
	size_t	i;

	sim = sim_ptr;
	i = 0;
	while (i < sim->num_phils)
	{
		sem_wait(sim->sems->num_eats);
		i++;
	}
	kill_philosophers(sim);
	free_sim(sim);
	exit(0);
}

static void	cleanup(t_sim *sim, pthread_t *threads, t_phil **philosophers)
{
	size_t		i;
	pthread_t	min_eats_thread;
	
	i = 0;
	pthread_create(&min_eats_thread, NULL, check_for_min_eats, sim);
	while (1)
	{
		if (waitpid(sim->philosopher_pids[i % sim->num_phils], NULL, WNOHANG) != 0)
			break;
		// pthread_join(threads[temp], NULL);
		i++;
	}
	kill_philosophers(sim);
	free_philosophers(philosophers);
	free_sim(sim);
	ft_free(&threads);
}

static t_sim	*init_sim(int argc, char **argv, t_phil ***philosophers)
{
	bool	success;
	t_sim	*sim;

	sim = create_simulation();
	if (sim == NULL)
		return (NULL);
	parse_args(sim, argc, argv, &success);
	if (success == false)
	{
		write(STDERR_FILENO, "Invalid arguments\n", 18);
		free_sim(sim);
		return (NULL);
	}
	*philosophers = create_philosophers(sim);
	if (*philosophers == NULL)
	{
		free_sim(sim);
		return (NULL);
	}
	return (sim);
}


void	kill_philosophers(t_sim *sim)
{
	size_t	i;

	i = 0;
	// printf("KILLING\n");
	while (i < sim->num_phils)
	{
		if (sim->philosopher_pids[i] != 0)
		{
			kill(sim->philosopher_pids[i], SIGKILL);
		}
		i++;
	}
	exit(0);
}


void	init_sems(const t_sim *sim, t_sems *sems)
{

	// printf("INITIALIZING num_forks semaphore with value %d\n", sim->num_phils);
	sem_unlink("/num_forks");
	sems->num_forks = sem_open("/num_forks", O_CREAT | O_EXCL, 0777, sim->num_phils);
	if (sems->num_forks == SEM_FAILED)
	{
		// sems->num_forks = sem_open("/num_forks", O_CREAT | O_EXCL, 0777, sim->num_phils);
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sem_unlink("/logging");
	sems->logging = sem_open("/logging", O_CREAT | O_EXCL, 0777, 1);
	if (sems->logging == SEM_FAILED)
	{
		// sems->logging = sem_open("/logging", O_CREAT | O_EXCL, 0777, 1);
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sem_unlink("/turn");
	sems->turn = sem_open("/turn", O_CREAT | O_EXCL, 0777, 1);
	if (sems->turn == SEM_FAILED)
	{
		// sems->turn = sem_open("/turn", O_CREAT | O_EXCL, 0777, 1);
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sem_unlink("/time");
	sems->time = sem_open("/time", O_CREAT | O_EXCL, 0777, 1);
	if (sems->time == SEM_FAILED)
	{
		// sems->time = sem_open("/time", O_CREAT | O_EXCL, 0777, 1);
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sem_unlink("/num_eats");
	sems->num_eats = sem_open("/num_eats", O_CREAT | O_EXCL, 0777, 0);
	if (sems->num_eats == SEM_FAILED)
	{
		// sems->num_eats = sem_open("/num_eats", O_CREAT | O_EXCL, 0777, 1);
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	
}


int	main(int argc, char **argv)
{
	t_sim		*sim;
	t_phil		**philosophers;
	pthread_t	*threads;
	size_t		i;
	t_sems		sems;

	sim = init_sim(argc, argv, &philosophers);
	if (sim == NULL)
		return (EXIT_FAILURE);
	threads = ft_calloc(sim->num_phils, sizeof(pthread_t));
	if (threads == NULL)
	{
		free_philosophers(philosophers);
		free_sim(sim);
		return (EXIT_FAILURE);
	}
	i = 0;
	init_sems(sim, &sems);
	sim->sems = &sems;
	while (i < sim->num_phils)
	{
		sim->philosopher_pids[i] = fork();
		if (sim->philosopher_pids[i] == 0)
		{
			// open_sems(sim, &sems);
			// sim->sems = &sems;
			run_sim(philosophers[i]);
		}
		i++;
	}
	
	// check_sim(sim, philosophers);
	// kill_philosophers(sim);
	cleanup(sim, threads, philosophers);
}
