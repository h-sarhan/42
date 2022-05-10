/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:12:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/10 10:03:31 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s) + 1;
	while (i < len)
	{
		if (s[i] == c)
			return ((char *) &s[i]);
		i++;
	}
	return (NULL);
}
