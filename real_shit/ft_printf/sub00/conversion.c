/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:21:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/21 07:26:20 by hsarhan          ###   ########.fr       */
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

int	print_conversion(t_conversion *conv, void *val)
{
	int	num_printed;
	int	precision_padding;
	int	min_width_padding;
	int	i;

	num_printed = 0;
	min_width_padding = 0;
	precision_padding = 0;
	// %s
	if (conv->type == 's')
	{
		int	num_chars = ft_strlen(*(char **)val);
		num_printed += num_chars;
		if (conv->min_width > num_printed)
		{
			min_width_padding = conv->min_width - num_printed;
			num_printed += min_width_padding;
		}
		if (conv->pad_right == FALSE)
		{
			// Pad left with spaces
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd(' ', STDOUT);
				i++;
			}
		}
		ft_putstr_fd(*(char **)val, STDOUT);
		if (conv->pad_right == TRUE)
		{
			// Pad right with spaces
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd(' ', STDOUT);
				i++;
			}
		}
	}
	// %c 
	if (conv->type == 'c')
	{
		int	num_chars = 1;
		num_printed += num_chars;
		if (conv->min_width > num_printed)
		{
			min_width_padding = conv->min_width - num_printed;
			num_printed += min_width_padding;
		}
		if (conv->pad_right == FALSE)
		{
			// Pad left with spaces
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd(' ', STDOUT);
				i++;
			}
		}
		ft_putchar_fd(*(char *)val, STDOUT);
		if (conv->pad_right == TRUE)
		{
			// Pad right with spaces
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd(' ', STDOUT);
				i++;
			}
		}
	}
	// %d or %i
	if (conv->type == 'd' || conv->type == 'i')
	{
		int	num_digits = count_digits_int(*(int *)val);
		num_printed += num_digits;
		if ((conv->space == TRUE || conv->sign == TRUE) && *(int *) val >= 0)
			num_printed += 1;
		if (conv->precision == TRUE && conv->precision_amount > num_digits)
		{
			precision_padding = conv->precision_amount - num_digits;
			num_printed += precision_padding;
		}
		if (conv->min_width > num_printed)
		{
			min_width_padding = conv->min_width - num_printed;
			num_printed += min_width_padding;
		}
		if (conv->pad_right == FALSE && (conv->pad_zeros == FALSE || conv->precision == TRUE))
		{
			// Pad left with spaces
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd(' ', STDOUT);
				i++;
			}
		}
		if (conv->space == TRUE  && conv->sign == FALSE && *(int *) val >= 0)
			ft_putchar_fd(' ', STDOUT);
		else if (conv->sign == TRUE && *(int *) val >= 0)
			ft_putchar_fd('+', STDOUT);
		if (conv->pad_zeros == TRUE && conv->precision == FALSE && conv->pad_right == FALSE)
		{
			// Pad left with zeros
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd('0', STDOUT);
				i++;
			}
		}
		if (conv->precision == TRUE)
		{
			// Add leading zeros to fill precision
			i = 0;
			while (i < precision_padding)
			{
				ft_putchar_fd('0', STDOUT);
				i++;
			}
		}
		ft_putnbr_fd(*(int *)val, STDOUT);
		if (conv->pad_right == TRUE)
		{
			// Pad right with spaces
			i = 0;
			while (i < min_width_padding)
			{
				ft_putchar_fd(' ', STDOUT);
				i++;
			}
		}
	}
	return (num_printed);
}
