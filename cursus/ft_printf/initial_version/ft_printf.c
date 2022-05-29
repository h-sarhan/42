/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:32:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/20 20:56:22 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_num_conversions(char conversion, va_list args)
{
	int				int_arg;
	unsigned int	uint_arg;	

	if (conversion == 'd' || conversion == 'i')
	{
		int_arg = va_arg(args, int);
		ft_putnbr_fd(int_arg, STDOUT);
		return (count_digits_int(int_arg));
	}
	if (conversion == 'u')
	{
		uint_arg = va_arg(args, unsigned int);
		print_unsigned_int(uint_arg);
		return (count_digits_unsigned(uint_arg));
	}
	if (conversion == 'x')
		return (print_hex_int(va_arg(args, unsigned int), LOWER));
	if (conversion == 'X')
		return (print_hex_int(va_arg(args, unsigned int), UPPER));
	if (conversion == 'p')
		return (print_hex_pointer(va_arg(args, void *)));
	return (-1);
}

int	handle_str_conversions(char conversion, va_list args)
{
	char			*str_arg;

	if (conversion == 'c')
	{
		ft_putchar_fd(va_arg(args, int), STDOUT);
		return (1);
	}
	if (conversion == 's')
	{
		str_arg = va_arg(args, char *);
		ft_putstr_fd(str_arg, STDOUT);
		return (ft_strlen(str_arg));
	}
	if (conversion == '%')
	{
		ft_putchar_fd('%', STDOUT);
		return (1);
	}
	return (-1);
}

int	handle_conversion(const char *fmt, va_list args, int *chars_printed)
{
	int	i;
	int	num_chars;

	i = 1;
	while (fmt[i] != '\0' && ft_strchr("cspdiuxX%", fmt[i]) == NULL)
		i++;
	if (fmt[i] == '\0')
		return (FALSE);
	if (ft_strchr("cs", fmt[i]) != NULL)
		num_chars = handle_str_conversions(fmt[i], args);
	else if (fmt[i] == '%')
	{
		num_chars = handle_str_conversions(fmt[i], args);
		i++;
	}
	else
		num_chars = handle_num_conversions(fmt[i], args);
	if (num_chars != -1)
	{
		*chars_printed += num_chars;
		return (TRUE);
	}
	else
		return (FALSE);
}

int	print_format_string(const char *fmt, va_list args)
{
	int	i;
	int	success;
	int	chars_printed;

	i = 0;
	success = TRUE;
	chars_printed = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			success = handle_conversion(&fmt[i], args, &chars_printed);
			i++;
		}
		else
		{
			ft_putchar_fd(fmt[i], STDOUT);
			chars_printed++;
		}
		if (!success)
			return (-1);
		i++;
	}
	return (chars_printed);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		chars_printed;

	va_start(args, fmt);
	chars_printed = print_format_string(fmt, args);
	va_end(args);
	return (chars_printed);
}
