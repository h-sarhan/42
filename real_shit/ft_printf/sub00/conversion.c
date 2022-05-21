/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:21:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/21 04:59:34 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conversion	*new_conversion(char *fmt)
{
	t_conversion	*conversion;

	conversion = malloc(sizeof(t_conversion));
	if (conversion == NULL)
		return (NULL);
	conversion->type = fmt[ft_strlen(fmt) - 1];
	conversion->precision = ft_strchr(fmt, '.') != NULL;
	conversion->alt_form = ft_strchr(fmt, '#') != NULL;
	conversion->space = ft_strchr(fmt, ' ') != NULL;
	conversion->sign = ft_strchr(fmt, '+') != NULL;
	conversion->pad_right = ft_strchr(fmt, '-') != NULL;
	conversion->pad_zeros = FALSE;
	parse_conversion_string(fmt, conversion);
	return (conversion);
}

void	parse_conversion_string(char *fmt, t_conversion *conv)
{
	int	i;
	
	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '0')
			conv->pad_zeros = TRUE;
		else if (ft_isdigit(fmt[i]) == TRUE)
		{
			conv->min_width = ft_atoi(&fmt[i]);
			break ;
		}
		i++;
	}
	if (conv->precision)
	{
		conv->precision_amount = ft_atoi(ft_strchr(fmt, '.') + 1);
	}
}
