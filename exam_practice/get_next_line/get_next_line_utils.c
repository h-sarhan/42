/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:10:29 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 11:10:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t n_members, size_t size)
{
	unsigned char	*memory;
	size_t			i;

	memory = malloc(n_members * size);
	if (memory == NULL)
		return (NULL);
	i = 0;
	while (i < n_members * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}