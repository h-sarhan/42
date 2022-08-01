/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:17:17 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/01 15:58:11 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(const int c)
{
	return (c >= '0' && c <= '9');
}

// Checks if an argument is numeric
static bool	is_numeric(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '+')
			return (false);
		if (str[i] == '+' && i != 0)
			return (false);
		if (str[i] == '+' && ft_strlen(str) == 1)
			return (false);
		i++;
	}
	return (true);
}

void	parse_args(t_sim *sim, const int argc, char **argv, bool *success)
{
	size_t	i;

	if (argc != 5 && argc != 6)
	{
		*success = false;
		return ;
	}
	i = 1;
	while (i < (size_t) argc)
	{
		if (!is_numeric(argv[i]) || ft_atol(argv[i]) == FAIL
			|| ft_atol(argv[i]) == 0)
		{
			*success = false;
			return ;
		}
		i++;
	}
	sim->num_phils = ft_atol(argv[1]);
	printf("number of philosophers: %u\n", sim->num_phils);
	sim->time_to_die = ft_atol(argv[2]);
	printf("time to die: %lu\n", sim->time_to_die);
	sim->time_to_eat = ft_atol(argv[3]);
	printf("time to eat: %lu\n", sim->time_to_eat);
	sim->time_to_sleep = ft_atol(argv[4]);
	printf("time to sleep: %lu\n", sim->time_to_sleep);
	sim->min_eats = 0;
	if (argc == 6)
		sim->min_eats = ft_atol(argv[5]);
	printf("min eats: %u\n", sim->min_eats);
	*success = true;
}
