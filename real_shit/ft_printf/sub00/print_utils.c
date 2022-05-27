/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:38:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/27 19:06:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex_pointer(void *pointer)
{
	ft_putstr_fd("0x", STDOUT);
	if (pointer == NULL)
	{
		ft_putchar_fd('0', STDOUT);
	}
	print_hex((unsigned long) pointer, 'x');
}

void	print_hex_int(unsigned int num, char hex_type)
{
	if (num == 0)
	{
		ft_putchar_fd('0', STDOUT);
		return ;
	}
	print_hex(num, hex_type);
}

void	print_n_chars(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar_fd(c, STDOUT);
		i++;
	}
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
