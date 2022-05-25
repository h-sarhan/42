/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:21:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/25 15:22:57 by hsarhan          ###   ########.fr       */
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
	conv->precision = ft_strchr(fmt, '.') != NULL;
	if (conv->precision && ft_isdigit(ft_strchr(fmt, '.')[1]))
		conv->precision = FALSE;
	conv->alt_form = ft_strchr(fmt, '#') != NULL;
	conv->space = ft_strchr(fmt, ' ') != NULL;
	conv->sign = ft_strchr(fmt, '+') != NULL;
	conv->pad_right = ft_strchr(fmt, '-') != NULL;
	conv->pad_zeros = FALSE;
	conv->mw_padding = 0;
	conv->pr_padding = 0;
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
		else if (ft_isdigit(fmt[i]))
		{
			conv->min_width = ft_atoi(&fmt[i]);
			while (ft_isdigit(fmt[i]) && fmt[i] != '\0')
				i++;
			if (fmt[i] == '\0' || conv->precision)
				break ;
		}
		else
			i++;
	}
	if (conv->precision)
		conv->precision_amount = ft_atoi(ft_strchr(fmt, '.') + 1);
}

void	calculate_padding(t_conversion *conv, void *val)
{	
	int	init_chrs;

	if (conv->type == 'x' || conv->type == 'X')
		init_chrs = count_hex(*(unsigned long *) val);
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
	if (ft_strchr("xXudi", conv->type) != NULL
		&& conv->precision && conv->precision_amount > init_chrs)
		conv->pr_padding = conv->precision_amount - init_chrs;
	if (conv->min_width > init_chrs + conv->pr_padding)
		conv->mw_padding = conv->min_width - conv->pr_padding - init_chrs;
	if (ft_strchr("xX", conv->type) != NULL && conv->alt_form)
		conv->mw_padding -= 2;
	if (ft_strchr("di", conv->type) != NULL
		&& (conv->space || conv->sign) && *(int *) val >= 0)
		conv->mw_padding -= 1;
}

int	print_hex_conversion(t_conversion *conv, unsigned long val)
{
	int	num_printed;

	num_printed = count_hex(val);
	if (conv->alt_form && val != 0)
		num_printed += 2;
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding + conv->pr_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->alt_form && val != 0)
	{
		ft_putchar_fd('0', STDOUT);
		ft_putchar_fd(conv->type, STDOUT);
	}
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->mw_padding);
	if (conv->precision)
		print_n_chars('0', conv->pr_padding);
	print_hex_int(val, conv->type);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

int	print_uint_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	num_printed = count_digits_unsigned(val);
	calculate_padding(conv, &val);
	if (conv->mw_padding > 0)
		num_printed += conv->mw_padding;
	if (conv->pr_padding > 0)
		num_printed += conv->pr_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->mw_padding);
	if (conv->precision)
		print_n_chars('0', conv->pr_padding);
	print_unsigned_int(val);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

int	print_pointer_conversion(t_conversion *conv, void *val)
{
	int	num_printed;

	num_printed = count_hex((unsigned long)val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding;
	if (!conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	print_hex_pointer(val);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

int	print_string_conversion(t_conversion *conv, char *val)
{
	int		num_printed;
	char	null_str[20];

	if (val == NULL)
	{
		ft_strlcpy(null_str, "(null)", 20);
		val = null_str;
	}
	num_printed = ft_strlen(val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding;
	if (!conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	ft_putstr_fd(val, STDOUT);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

int	print_char_conversion(t_conversion *conv, char val)
{
	int	num_printed;

	num_printed = 1;
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding;
	if (!conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	ft_putchar_fd(val, STDOUT);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

int	print_int_conversion(t_conversion *conv, int val)
{
	int	num_printed;

	num_printed = count_digits_int(val);
	calculate_padding(conv, &val);
	if (conv->mw_padding > 0)
		num_printed += conv->mw_padding;
	if (conv->pr_padding > 0)
		num_printed += conv->pr_padding;
	if (conv->space || conv->sign)
		num_printed++;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->space && !conv->sign && val >= 0)
		ft_putchar_fd(' ', STDOUT);
	else if (conv->sign && val >= 0)
		ft_putchar_fd('+', STDOUT);
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->mw_padding);
	if (conv->precision)
		print_n_chars('0', conv->pr_padding);
	ft_putnbr_fd(val, STDOUT);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

int	print_conversion(t_conversion *conv, void *val)
{
	if (conv->type == 'x' || conv->type == 'X')
		return (print_hex_conversion(conv, *(unsigned long *) val));
	else if (conv->type == 'u')
		return (print_uint_conversion(conv, *(unsigned int *) val));
	else if (conv->type == 'p')
		return (print_pointer_conversion(conv, *(void **)val) + 2);
	else if (conv->type == 's')
		return (print_string_conversion(conv, *(char **) val));
	else if (conv->type == 'c')
		return (print_char_conversion(conv, *(char *) val));
	else if (conv->type == '%')
		return (print_char_conversion(conv, '%'));
	else if (conv->type == 'd' || conv->type == 'i')
		return (print_int_conversion(conv, *(int *) val));
	else
		return (-1);
}
