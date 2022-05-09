/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:47:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/09 17:44:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_lib.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*bytes;
	unsigned char	val;
	size_t			i;

	bytes = b;
	val = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		bytes[i] = val;
		i++;
	}
	return (b);
}
