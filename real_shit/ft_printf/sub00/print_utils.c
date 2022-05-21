/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:38:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/21 09:42:17 by hsarhan          ###   ########.fr       */
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

char	dec_to_hex(unsigned char dec, char hex_type)
{
	if (dec > 9)
	{
		if (hex_type == 'X')
			return (dec + 'A' - 10);
		else
			return (dec + 'a' - 10);
	}
	return (dec + '0');
}

int	print_hex(unsigned long num, char hex_type)
{
	unsigned char	*bytes;
	unsigned char	hex_char;
	int				i;
	int				chars_printed;

	bytes = (unsigned char *) &num;
	i = 7;
	chars_printed = 0;
	while (i >= 0)
	{
		hex_char = bytes[i] >> 4;
		if (hex_char != 0 || chars_printed > 0)
		{
			ft_putchar_fd(dec_to_hex(hex_char, hex_type), STDOUT);
			chars_printed++;
		}
		hex_char = bytes[i] & 0x0f;
		if (hex_char != 0 || chars_printed > 0)
		{
			ft_putchar_fd(dec_to_hex(hex_char, hex_type), STDOUT);
			chars_printed++;
		}
		i--;
	}
	return (chars_printed);
}

int	print_hex_pointer(void *pointer)
{
	ft_putstr_fd("0x", STDOUT);
	if (pointer == NULL)
	{
		ft_putchar_fd('0', STDOUT);
		return (3);
	}
	return (2 + print_hex((unsigned long) pointer, 'x'));
}

int	print_hex_int(unsigned int num, char hex_type)
{
	if (num == 0)
	{
		ft_putchar_fd('0', STDOUT);
		return (1);
	}
	else
		return (print_hex(num, hex_type));
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
