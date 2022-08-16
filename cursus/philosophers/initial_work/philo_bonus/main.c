/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/16 15:52:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Tests: 
// ? valgrind --tool=helgrind --history-level=none  ./philo 5 800 200 200 7
// * ./philo 1 800 200 200: Should not eat and die
// * ./philo 5 800 200 200 7: No one should die
// * ./philo 4 410 200 200: No one should die
// * ./philo 4 310 200 100: A philosopher should die
// Philosophers

//  ./philo 100 800 200 200
//  ./philo 200 800 200 200
// * ./philo 3 1000 500 600
// * ./philo 5 200 100 60
// * ./philo 4 500 400 300
// * ./philo 3 700 200 200 Philosophers shouldnt die here
// * ./philo 199 800 200 100

static void	cleanup(t_sim *sim, pthread_t *threads, t_phil **philosophers)
{
	size_t	temp;

	temp = 0;
	while (temp < sim->num_phils)
	{
		// pthread_join(threads[temp], NULL);
		temp++;
	}
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

static void	check_sim(t_sim *sim, t_phil **philosophers)
{
	bool	all_ate;
	size_t	i;

	while (read_sim_status(sim) == true)
	{
		if (sim->min_eats > 0)
		{
			i = 0;
			all_ate = true;
			while (i < sim->num_phils)
			{
				if (read_num_eats(philosophers[i]) < sim->min_eats)
					all_ate = false;
				i++;
			}
			if (all_ate == true)
			{
				// pthread_mutex_lock(&sim->status_mutex);
				sim->status = false;
				// pthread_mutex_unlock(&sim->status_mutex);
				break ;
			}
		}
	}
}

void	init_sems(const t_sim *sim, t_sems *sems)
{
	unsigned int	i;
	char			*phil_name;

	sems->num_forks = sem_open("/num_forks", O_CREAT | O_RDWR, 0644, sim->num_phils);
	if (sems->num_forks == SEM_FAILED)
	{
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sems->logging = sem_open("/logging", O_CREAT | O_RDWR, 0644, 1);
	if (sems->logging == SEM_FAILED)
	{
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sems->status = sem_open("/status", O_CREAT | O_RDWR, 0644, 1);
	if (sems->status == SEM_FAILED)
	{
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	i = 0;
	// ! REPLACE THIS WITH LIBFT VERSION
	phil_name = strdup("/0");
	sems->num_eats = ft_calloc(sim->num_phils, sizeof(sem_t *));
	while (i < sim->num_phils)
	{
		phil_name[1] = i + 1;
		sems->num_eats[i] = sem_open(phil_name, O_CREAT | O_RDWR, 0644, 1);
		i++;
	}
	free(phil_name);
}

void	open_sems(const t_sim *sim, t_sems *sems)
{
	unsigned int	i;
	char			*phil_name;

	sems->num_forks = sem_open("/num_forks", O_RDWR);
	if (sems->num_forks == SEM_FAILED)
	{
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sems->logging = sem_open("/logging", O_RDWR);
	if (sems->logging == SEM_FAILED)
	{
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	sems->status = sem_open("/status", O_RDWR);
	if (sems->status == SEM_FAILED)
	{
		// ! BETTER ERROR HANDLING
		exit(EXIT_FAILURE);
	}
	i = 0;
	// ! REPLACE THIS WITH LIBFT VERSION
	phil_name = strdup("/0");
	while (i < sim->num_phils)
	{
		phil_name[1] = i + 1;
		sems->num_eats[i] = sem_open(phil_name, O_RDWR);
		i++;
	}
	free(phil_name);
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
	while (i < sim->num_phils)
	{
		sim->philosopher_pids[i] = fork();
		// usleep(350);
		if (sim->philosopher_pids[i] == 0)
		{
			open_sems(sim, &sems);
			run_sim(philosophers[i]);
		}
		i++;
	}
	check_sim(sim, philosophers);
	cleanup(sim, threads, philosophers);
}
