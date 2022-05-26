/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:10:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/26 18:29:13 by hsarhan          ###   ########.fr       */
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

void	print_hex(unsigned long num, char hex_type)
{
	unsigned char	*bytes;
	unsigned char	hex_char;
	int				i;
	t_bool			start;

	bytes = (unsigned char *) &num;
	i = 7;
	start = FALSE;
	while (i >= 0)
	{
		hex_char = bytes[i] >> 4;
		if (hex_char != 0 || start == TRUE)
		{
			ft_putchar_fd(dec_to_hex(hex_char, hex_type), STDOUT);
			start = TRUE;
		}
		hex_char = bytes[i] & 0x0f;
		if (hex_char != 0 || start == TRUE)
		{
			ft_putchar_fd(dec_to_hex(hex_char, hex_type), STDOUT);
			start = TRUE;
		}
		i--;
	}
}
