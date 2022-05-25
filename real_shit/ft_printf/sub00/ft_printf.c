/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:32:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/25 15:42:08 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	int		i;
	char	*chars_printed;
	int		conv_start;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			conv_start = &fmt[i];
		}
		i++;
	}
	return (i);
}
