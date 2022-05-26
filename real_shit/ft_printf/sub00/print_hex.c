/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:10:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/26 16:11:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
