/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:38:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/18 23:15:39 by hsarhan          ###   ########.fr       */
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

char	dec_to_hex(unsigned char dec, int print_upper)
{
	if (dec > 9)
	{
		if (print_upper == TRUE)
			return (dec + 'A' - 10);
		else
			return (dec + 'a' - 10);
	}
	return (dec + '0');
}

void	print_hex(unsigned long num, int print_upper)
{
	unsigned char	*bytes;
	unsigned char	left;
	unsigned char	right;
	int				i;
	int				start;

	bytes = (unsigned char *) &num;
	i = 7;
	start = FALSE;
	while (i >= 0)
	{
		left = bytes[i] >> 4;
		if (left != 0 || start == TRUE)
		{
			ft_putchar_fd(dec_to_hex(left, print_upper), STDOUT);
			start = TRUE;
		}
		right = bytes[i] & 0x0f;
		if (right != 0 || start == TRUE)
		{
			ft_putchar_fd(dec_to_hex(right, print_upper), STDOUT);
			start = TRUE;
		}
		i--;
	}
}

void	print_hex_pointer(void *pointer)
{
	ft_putstr_fd("FT_PRINTF: ", STDOUT);
	if (pointer == NULL)
		ft_putstr_fd("(null)", STDOUT);
	else
	{
		ft_putstr_fd("0x", STDOUT);
		print_hex((unsigned long) pointer, LOWER);
	}
}

void	print_hex_int(unsigned int num, int print_upper)
{
	ft_putstr_fd("FT_PRINTF: ", STDOUT);
	if (num == 0)
		ft_putchar_fd('0', STDOUT);
	else
		print_hex(num, print_upper);
}
