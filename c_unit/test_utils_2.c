/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:25:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/07 00:54:26 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

int	atoi_range(char *str, int start, int end)
{
	char	*str_copy;
	int		i;
	int		res;

	str_copy = malloc(sizeof(char) * (end - start + 2));
	i = start;
	while (i <= end)
	{
		str_copy[i - start] = str[i];
		i++;
	}
	str_copy[i] = '\0';
	res = atoi(str_copy);
	free(str_copy);
	return (res);
}

int	count_nums_in_str(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			size++;
		while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (size);
}

int	*str_to_ints(char *str, int *len)
{
	int	num_start;
	int	i;
	int	*ints;
	int	ints_idx;

	*len = count_nums_in_str(str);
	ints = malloc(sizeof(int) * *len);
	i = 0;
	ints_idx = 0;
	num_start = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
			num_start = i;
		while ((str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
			&& str[i] != '\0')
			i++;
		if (num_start >= 0)
			ints[ints_idx++] = atoi_range(str, num_start, i - 1);
		if (str[i] == '\0')
			break ;
		i++;
		num_start = -1;
	}
	return (ints);
}

void	test_util_putnbr(int nb, char *color)
{
	char	nb_as_char;

	write(1, color, 5);
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		test_util_putnbr(nb / 10, color);
		nb %= 10;
	}
	if (nb < 10)
	{
		nb_as_char = nb + '0';
		write(1, &nb_as_char, 1);
	}
}

int	test_util_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
