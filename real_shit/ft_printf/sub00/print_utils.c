/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:38:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/26 18:29:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	print_unsigned_int(unsigned int num)
{
	if (num < 10)
	{
		ft_putchar_fd(num + '0', 1);
	}
	else
	{
		ft_putnbr_fd(num / 10, 1);
		ft_putchar_fd(num % 10 + '0', 1);
	}
}

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
	}
	else
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
