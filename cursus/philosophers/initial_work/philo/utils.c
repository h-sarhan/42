/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:30:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/13 10:30:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Classic strlen
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// Frees memory if it is not NULL
// Sets it to NULL after freeing
// Takes a *POINTER* to the memory being freed
void	ft_free(void *memory)
{
	if (*(void **)memory != NULL)
		free(*(void **)memory);
	*(void **)memory = NULL;
}

// Checks if a character is whitespace
static bool	is_space(const char c)
{
	return (c == ' ' || c == '\f'
		|| c == '\n' || c == '\r'
		|| c == '\t' || c == '\v');
}

// Ascii string to unsigned int, checks for overflow while doing the conversion
long	atoui(const char *str)
{
	long	num;
	int		i;
	int		sign;

	num = 0;
	i = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (FAIL);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += str[i++] - '0';
		if (num > UINT_MAX)
			return (FAIL);
	}
	return (num * sign);
}

// Calloc
void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	if (count != 0 && size != 0 && count > SIZE_MAX / size)
		return (NULL);
	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	memset(memory, 0, count * size);
	return (memory);
}

// TODO: Make this return an error when sim ends while sleeping
int	sleepsleep(t_phil *phil, t_time_ms sleep_time)
{
	t_time_ms	time_slept;
	t_timeval	start_time;

	time_slept = 0;
	get_start_time(&start_time);
	while (time_slept < sleep_time && read_sim_status(phil->sim) == true &&
			get_micro_time(phil->phil_eat_time) < phil->sim->time_to_die * 1000)
	{
		usleep(60);
		time_slept = get_micro_time(&start_time);
	}
	if (time_slept < sleep_time)
		return (FAIL);
	return (SUCCESS);
}