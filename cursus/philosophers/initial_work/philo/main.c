/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:54:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 12:36:28 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Philosophers
int	main(int argc, char **argv)
{
	t_simulation	*sim;
	t_time_ms		time_ms;
	
	sim = create_simulation();
	usleep(10000);
	time_ms = get_time(sim->start_time);
	printf("%lu\n", time_ms);
	free_sim(sim);
}
