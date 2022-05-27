/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:45:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/26 20:08:25 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	num_printed = count_hex(val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding + conv->pr_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->alt_form && val != 0)
	{
		num_printed += 2;
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
	num_printed += conv->mw_padding + conv->pr_padding;
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

int	print_int_conversion(t_conversion *conv, int val)
{
	int	num_printed;

	num_printed = count_digits_int(val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding + conv->pr_padding;
	if ((conv->space || conv->sign) && val >= 0)
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
