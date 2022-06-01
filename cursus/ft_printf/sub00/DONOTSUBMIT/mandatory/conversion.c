/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:21:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/27 22:43:37 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Creates and initialises a new conversion struct
t_conversion	*new_conversion(char *fmt)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	if (conv == NULL)
		return (NULL);
	conv->type = fmt[ft_strlen(fmt) - 1];
	conv->precision = FALSE;
	conv->alt_form = FALSE;
	conv->space = FALSE;
	conv->sign = FALSE;
	conv->pad_right = FALSE;
	conv->pad_zeros = FALSE;
	conv->min_width = 0;
	conv->precision_amount = 0;
	conv->mw_padding = 0;
	conv->pr_padding = 0;
	return (conv);
}

// Counts the the characters to be printed for a value without 
// extra padding/flags
int	count_initial_chars(t_conversion *conv, void *val)
{
	int	init_chrs;

	if (conv->type == 'x' || conv->type == 'X')
		init_chrs = count_hex(*(unsigned int *) val);
	else if (conv->type == 'u')
		init_chrs = count_digits_unsigned(*(unsigned int *) val);
	else if (conv->type == 'p')
		init_chrs = count_hex(*(unsigned long *) val) + 2;
	else if (conv->type == 's')
		init_chrs = ft_strlen(*(char **) val);
	else if (conv->type == 'c' || conv->type == '%')
		init_chrs = 1;
	else
		init_chrs = count_digits_int(*(int *) val);
	return (init_chrs);
}

// Prints a conversion
// Handles the following conversions
// 1. Hexadecimal 'x' or 'X'
// 2. Unsigned int 'u'
// 3. Void Pointer 'p'
// 4. String 's'
// 5. Character 'c'
// 6. Percent '%'
// 7. Integer 'd' or 'i'
int	print_conversion(t_conversion *conv, va_list args)
{
	if (conv->type == 'x' || conv->type == 'X')
		return (print_hex_conversion(conv, va_arg(args, unsigned int)));
	else if (conv->type == 'u')
		return (print_uint_conversion(conv, va_arg(args, unsigned int)));
	else if (conv->type == 'p')
		return (print_pointer_conversion(conv, va_arg(args, void *)) + 2);
	else if (conv->type == 's')
		return (print_string_conversion(conv, va_arg(args, char *)));
	else if (conv->type == 'c')
		return (print_char_conversion(conv, (char) va_arg(args, int)));
	else if (conv->type == '%')
		return (print_char_conversion(conv, '%'));
	else if (conv->type == 'd' || conv->type == 'i')
		return (print_int_conversion(conv, va_arg(args, int)));
	else
		return (-1);
}
