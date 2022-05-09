/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:45:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/09 18:03:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_lib.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*dst_bytes;
	const char	*src_bytes;
	size_t		i;

	dst_bytes = dst;
	src_bytes = src;
	i = 0;
	while (i < len)
	{
		dst_bytes[i] = src_bytes[i];
		i++;
	}
	return (dst);
}
