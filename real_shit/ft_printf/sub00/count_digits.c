/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:34:38 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/21 07:52:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_digits_int(int num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	if (num == INT_MIN)
		return (11);
	if (num < 0)
	{
		num_digits += 1;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		num_digits++;
	}
	return (num_digits);
}

int	count_digits_unsigned(unsigned int num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		num_digits++;
	}
	return (num_digits);
}

int	count_hex(unsigned long num)
{
	unsigned char	*bytes;
	unsigned char	hex_char;
	int				i;
	int				num_hex;

	if (num == 0)
		return (3);
	bytes = (unsigned char *) &num;
	i = 7;
	num_hex = 0;
	while (i >= 0)
	{
		hex_char = bytes[i] >> 4;
		if (hex_char != 0 || num_hex > 0)
			num_hex++;
		hex_char = bytes[i] & 0x0f;
		if (hex_char != 0 || num_hex > 0)
			num_hex++;
		i--;
	}
	return (num_hex + 2);
}
