/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:38:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/18 01:05:24 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
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

void	print_hex(unsigned long num)
{
	unsigned char	*bytes;
	int		i;
	unsigned char	left;
	unsigned char	right;


	bytes = (char *) &num;
	i = 0;
	while (i < 8)
	{
		printf("BYTE %d = %d\n", i + 1, bytes[i]);
		printf("Left 4 bits = %d\n", bytes[i] >> 4);
		printf("Right 4 bits = %d\n", bytes[i] & 0x0f);
		i++;
	}
}
