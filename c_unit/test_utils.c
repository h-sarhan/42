/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:53:55 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/01 17:30:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

void	print_int_array(int *arr, int arr_len)
{
	int	idx;

	idx = 0;
	write(1, YELLOW, 5);
	write(1, "[", 1);
	while (idx < arr_len - 1)
	{
		ft_putnbr(arr[idx]);
		write(1, ", ", 2);
		idx++;
	}
	ft_putnbr(arr[idx]);
	write(1, "]\n", 2);
	write(1, RESET, 5);
}

void	print_msg_color(char *msg, char *color)
{
	write(1, color, 5);
	while (*msg != '\0')
	{
		write(1, msg, 1);
		msg++;
	}
	write(1, RESET, 5);
}

void	ft_putnbr(int nb)
{
	char	nb_as_char;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		nb %= 10;
	}
	nb_as_char = nb + '0';
	write(1, &nb_as_char, 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
