/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:45:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/11 11:44:45 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	total_length;
	unsigned int	num_chars_to_copy;
	unsigned int	chars_copied;

	if (dstsize < ft_strlen(dest))
		total_length = str_length(src) + size;
	else
		total_length = ft_strlen(src) + ft_strlen(dest);
	if (dstsize >= ft_strlen(dest) + 1)
		num_chars_to_copy = size - ft_strlen(dest) - 1;
	else
		return (total_length);
	chars_copied = 0;
	while (*dest != '\0')
		dest++;
	while (*src != '\0' && chars_copied < num_chars_to_copy)
	{
		*dest = *src;
		dest++;
		src++;
		chars_copied++;
	}
	*dest = '\0';
	return (total_length);
}
