/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:32:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/25 21:08:37 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
void	print_conv_params(t_conversion *conv);

int	ft_printf(const char *fmt, ...)
{
	int				i;
	//char			*chars_printed;
	int				conv_start;
	int				conv_len;
	char			*conv_str;
	t_conversion	*conv;
	va_list			args;

	i = 0;
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			conv_start = i;
			conv_len = 0;
			while (conv_len == 0 || ft_strchr("%diuxXcsp", fmt[i]) == NULL)
			{
				i++;
				conv_len++;
			}
			conv_str = ft_substr(fmt, conv_start, conv_len + 1);
			conv = new_conversion(conv_str);
			//print_conv_params(conv);
			print_conversion(conv, args);
			free(conv_str);
			free(conv);
		}
		else
			ft_putchar_fd(fmt[i], STDOUT);
		i++;
	}
	va_end(args);
	return (i);
}
