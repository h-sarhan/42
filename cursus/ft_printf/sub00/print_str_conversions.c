/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:50:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/27 22:55:51 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Prints a string conversion
int	print_string_conversion(t_conversion *conv, char *val)
{
	int		num_printed;
	char	null_str[20];
	int		i;

	if (conv->type != 's')
		return (-1);
	if (val == NULL)
	{
		ft_strlcpy(null_str, "(null)", 20);
		val = null_str;
	}
	num_printed = 0;
	i = 0;
	while (val[i] != '\0')
	{
		ft_putchar_fd(val[i], STDOUT);
		i++;
		num_printed++;
	}
	return (num_printed);
}

// Prints a character conversion
int	print_char_conversion(t_conversion *conv, char val)
{
	int	num_printed;

	if (conv->type != 'c' && conv->type != '%')
		return (-1);
	ft_putchar_fd(val, STDOUT);
	num_printed = 1;
	return (num_printed);
}
