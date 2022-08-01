/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 14:37:31 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Philosophers
int	main(int argc, char **argv)
{
	t_sim		*sim;
	t_time_ms	time_ms;
	bool		success;

	(void)argc, (void)argv;
	sim = create_simulation();
	if (sim == NULL)
		return (EXIT_FAILURE);
	usleep(10000);
	time_ms = get_time(sim, &success);
	if (!success)
	{
		free_sim(sim);
		return (EXIT_FAILURE);
	}
	printf("%lu\n", time_ms);
	free_sim(sim);
}
