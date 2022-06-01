/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:45:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/27 22:51:49 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Prints a hexadecimal conversion 'x' or 'X'
int	print_hex_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	if (conv->type != 'x' && conv->type != 'X')
		return (-1);
	num_printed = count_hex(val);
	print_hex_int(val, conv->type);
	return (num_printed);
}

// Prints an unsigned int conversion 'u'
int	print_uint_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	if (conv->type != 'u')
		return (-1);
	num_printed = count_digits_unsigned(val);
	print_unsigned_int(val);
	return (num_printed);
}

// Prints a pointer conversion 'p'
int	print_pointer_conversion(t_conversion *conv, void *val)
{
	int	num_printed;

	if (conv->type != 'p')
		return (-1);
	num_printed = count_hex((unsigned long)val);
	print_hex_pointer(val);
	return (num_printed);
}

// Prints an integer conversion 'd' or 'i'
int	print_int_conversion(t_conversion *conv, int val)
{
	int	num_printed;

	if (conv->type != 'd' && conv->type != 'i')
		return (-1);
	num_printed = count_digits_int(val);
	print_int(val, 0);
	return (num_printed);
}
