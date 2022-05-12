/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:44:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/12 20:22:01 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*bytes1;
	const unsigned char	*bytes2;
	size_t				i;

	bytes1 = s1;
	bytes2 = s2;
	i = 0;
	while (i < n)
	{
		if (bytes1[i] > bytes2[i])
			return (1);
		else if (bytes1[i] < bytes2[i])
			return (-1);
		i++;
	}
	return (0);
}

