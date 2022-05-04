/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:25:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 22:54:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

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
