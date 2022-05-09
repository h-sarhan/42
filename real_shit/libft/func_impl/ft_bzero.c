/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:27:59 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/09 13:34:52 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_lib.h"

void	ft_bzero(void *s, size_t n)
{
	char		*bytes;
	size_t		i;

	if (n == 0)
		return ;
	bytes = s;
	i = 0;
	while (i < n)
	{
		bytes[i] = 0;
		i++;
	}
}
