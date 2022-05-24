/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:21:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/24 20:03:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conversion	*new_conversion(char *fmt)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	if (conv == NULL)
		return (NULL);
	conv->type = fmt[ft_strlen(fmt) - 1];
	conv->precision = ft_strchr(fmt, '.') != NULL && ft_isdigit(ft_strchr(fmt, '.')[1]);
	conv->alt_form = ft_strchr(fmt, '#') != NULL;
	conv->space = ft_strchr(fmt, ' ') != NULL;
	conv->sign = ft_strchr(fmt, '+') != NULL;
	conv->pad_right = ft_strchr(fmt, '-') != NULL;
	conv->pad_zeros = FALSE;
	conv->min_width_padding = 0;
	conv->precision_padding = 0;
	parse_conversion_string(fmt, conv);
	return (conv);
}

void	parse_conversion_string(char *fmt, t_conversion *conv)
{
	int	i;
	
	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '0')
		{
			conv->pad_zeros = TRUE;
			i++;
		}
		else if (ft_isdigit(fmt[i]) == TRUE)
		{
			conv->min_width = ft_atoi(&fmt[i]);
			while (ft_isdigit(fmt[i]) == TRUE && fmt[i] != '\0')
				i++;
			if (fmt[i] == '\0' || conv->precision == TRUE)
				break ;
		}
		else
			i++;
	}
	if (conv->precision)
		conv->precision_amount = ft_atoi(ft_strchr(fmt, '.') + 1);
}
void	calculate_padding(t_conversion *conv, void *val);

int	print_hex_conversion(t_conversion *conv, unsigned long val)
{
	int	num_printed;

	num_printed = count_hex(val);
	if (conv->alt_form && val != 0 )
		num_printed += 2;
	calculate_padding(conv, &val);
	num_printed += conv->min_width_padding + conv->precision_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->min_width_padding);
	if (conv->alt_form && val != 0)
	{
		ft_putchar_fd('0', STDOUT);
		ft_putchar_fd(conv->type, STDOUT);
	}
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->min_width_padding);
	if (conv->precision)
		print_n_chars('0', conv->precision_padding);
	print_hex_int(val, conv->type);
	if (conv->pad_right)
		print_n_chars(' ', conv->min_width_padding);
	return (num_printed);
}

void	calculate_padding(t_conversion *conv, void *val)
{	
	int	initial_chars;

	if (conv->type == 'x' || conv->type == 'X')
	{
		initial_chars = count_hex(*(unsigned long *) val);
		if (conv->precision && conv->precision_amount > initial_chars)
			conv->precision_padding = conv->precision_amount - initial_chars;
		if (conv->min_width > initial_chars + conv->precision_padding)
			conv->min_width_padding = conv->min_width - conv->precision_padding - initial_chars;
		if (conv->alt_form)
			conv->min_width_padding -= 2;
	}
	if (conv->type == 'u')
	{
		initial_chars = count_digits_unsigned(*(unsigned int *) val);
		if (conv->precision && conv->precision_amount > initial_chars)
			conv->precision_padding = conv->precision_amount - initial_chars;
		if (conv->min_width > initial_chars + conv->precision_padding)
			conv->min_width_padding = conv->min_width - conv->precision_padding - initial_chars;
	}
}


int	print_uint_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	num_printed = count_digits_unsigned(val);
	calculate_padding(conv, &val);
	num_printed += conv->min_width_padding + conv->precision_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->min_width_padding);
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->min_width_padding);
	if (conv->precision)
		print_n_chars('0', conv->precision_padding);
	print_unsigned_int(val);
	if (conv->pad_right)
		print_n_chars(' ', conv->min_width_padding);
	return (num_printed);
}

int	print_conversion(t_conversion *conv, void *val)
{
	if (conv->type == '%')
	{
		ft_putchar_fd('%', STDOUT);
		return (1);
	}
	else if (conv->type == 'x' || conv->type == 'X')
		return (print_hex_conversion(conv, *(unsigned long *) val));
	else if (conv->type == 'u')
		return (print_uint_conversion(conv, *(unsigned int *) val));
	else
		return (-1);
	
//	// %u
//	{
//		int	initial_chars = count_digits_unsigned(*(unsigned int *)val);
//		num_printed += initial_chars;
//		if (conv->precision == TRUE && conv->precision_amount > initial_chars)
//		{
//			precision_padding = conv->precision_amount - initial_chars;
//			num_printed += precision_padding;
//		}
//		if (conv->min_width > num_printed)
//		{
//			min_width_padding = conv->min_width - num_printed;
//			num_printed += min_width_padding;
//		}
//		if (conv->pad_right == FALSE && (conv->pad_zeros == FALSE || conv->precision == TRUE))
//		{
//			// Pad left with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//		if (conv->pad_zeros == TRUE && conv->precision == FALSE && conv->pad_right == FALSE)
//		{
//			// Pad left with zeros
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd('0', STDOUT);
//				i++;
//			}
//		}
//		if (conv->precision == TRUE)
//		{
//			// Add leading zeros to fill precision
//			i = 0;
//			while (i < precision_padding)
//			{
//				ft_putchar_fd('0', STDOUT);
//				i++;
//			}
//		}
//		print_unsigned_int(*(unsigned int *)val);
//		if (conv->pad_right == TRUE)
//		{
//			// Pad right with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//	}
//	// %p
//	if (conv->type == 'p')
//	{
//		int	initial_chars = count_hex(*(unsigned long *)val) + 2;
//		num_printed += initial_chars;
//		if (conv->min_width > num_printed)
//		{
//			min_width_padding = conv->min_width - num_printed;
//			num_printed += min_width_padding;
//		}
//		if (conv->pad_right == FALSE)
//		{
//			// Pad left with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//		print_hex_pointer(*(void **)val);
//		if (conv->pad_right == TRUE)
//		{
//			// Pad right with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//	}
//	// %s
//	if (conv->type == 's')
//	{
//		int	initial_chars = ft_strlen(*(char **)val);
//		num_printed += initial_chars;
//		if (conv->min_width > num_printed)
//		{
//			min_width_padding = conv->min_width - num_printed;
//			num_printed += min_width_padding;
//		}
//		if (conv->pad_right == FALSE)
//		{
//			// Pad left with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//		ft_putstr_fd(*(char **)val, STDOUT);
//		if (conv->pad_right == TRUE)
//		{
//			// Pad right with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//	}
//	// %c 
//	if (conv->type == 'c')
//	{
//		int	initial_chars = 1;
//		num_printed += initial_chars;
//		if (conv->min_width > num_printed)
//		{
//			min_width_padding = conv->min_width - num_printed;
//			num_printed += min_width_padding;
//		}
//		if (conv->pad_right == FALSE)
//		{
//			// Pad left with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//		ft_putchar_fd(*(char *)val, STDOUT);
//		if (conv->pad_right == TRUE)
//		{
//			// Pad right with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//	}
//	// %d or %i
//	if (conv->type == 'd' || conv->type == 'i')
//	{
//		int	initial_chars = count_digits_int(*(int *)val);
//		num_printed += initial_chars;
//		if ((conv->space == TRUE || conv->sign == TRUE) && *(int *) val >= 0)
//			num_printed += 1;
//		if (conv->precision == TRUE && conv->precision_amount > initial_chars)
//		{
//			precision_padding = conv->precision_amount - initial_chars;
//			num_printed += precision_padding;
//		}
//		if (conv->min_width > num_printed)
//		{
//			min_width_padding = conv->min_width - num_printed;
//			num_printed += min_width_padding;
//		}
//		if (conv->pad_right == FALSE && (conv->pad_zeros == FALSE || conv->precision == TRUE))
//		{
//			// Pad left with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//		if (conv->space == TRUE  && conv->sign == FALSE && *(int *) val >= 0)
//			ft_putchar_fd(' ', STDOUT);
//		else if (conv->sign == TRUE && *(int *) val >= 0)
//			ft_putchar_fd('+', STDOUT);
//		if (conv->pad_zeros == TRUE && conv->precision == FALSE && conv->pad_right == FALSE)
//		{
//			// Pad left with zeros
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd('0', STDOUT);
//				i++;
//			}
//		}
//		if (conv->precision == TRUE)
//		{
//			// Add leading zeros to fill precision
//			i = 0;
//			while (i < precision_padding)
//			{
//				ft_putchar_fd('0', STDOUT);
//				i++;
//			}
//		}
//		ft_putnbr_fd(*(int *)val, STDOUT);
//		if (conv->pad_right == TRUE)
//		{
//			// Pad right with spaces
//			i = 0;
//			while (i < min_width_padding)
//			{
//				ft_putchar_fd(' ', STDOUT);
//				i++;
//			}
//		}
//	}
}
