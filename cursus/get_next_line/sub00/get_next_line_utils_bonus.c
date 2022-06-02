/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:31:16 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/02 20:31:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*resize(char **arr, int old_len, int new_len)
{
	int		i;
	char	*new_arr;
	
	i = 0;
	new_arr = malloc(new_len * sizeof(char));
	// new_arr = ft_calloc(new_len, sizeof(char));
	if (new_arr == NULL)
	{
		free(*arr);
		return (NULL);
	}
	while (i < old_len && i < new_len && (*arr)[i] != '\0')
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	// if (term == TRUE)
	// int j = i;
	while (i < new_len)
		new_arr[i++] = '\0';
	// *arr = new_arr;
	return (new_arr);
}

// void    ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*bytes;
// 	size_t			i;

// 	if (n == 0)
// 		return ;
// 	bytes = s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		bytes[i] = 0;
// 		i++;
// 	}
// }


// void	*ft_calloc(size_t count, size_t size)
// {
// 	unsigned char	*memory;

// 	if (count != 0 && size != 0 && count > SIZE_MAX / size)
// 		return (NULL);
// 	memory = malloc(count * size);
// 	if (memory == NULL)
// 		return (NULL);
// 	ft_bzero(memory, count * size);
// 	return (memory);
// }
