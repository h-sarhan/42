/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:55:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 11:08:37 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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

void	resize(char **arr, size_t old_len, size_t new_len)
{
	char	*new_arr;
	size_t	i;

	new_arr = ft_calloc(new_len + 1, sizeof(char));
	if (new_arr == NULL)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	(*arr) = new_arr;
}

char	*get_next_line(int fd)
{
	char	ch;
	char	*buff;
	size_t	buff_size;
	size_t	chars_read;

	buff_size = 100;
	buff = ft_calloc(buff_size + 1, sizeof(char));
	if (buff == NULL)
		return (NULL);
	chars_read = 0;
	read(fd, &ch, 1);
	while (ch != '\n')
	{
		buff[chars_read] = ch;
		chars_read++;
		if (chars_read >= buff_size)
		{
			resize(&buff, buff_size, buff_size * 2);
			buff_size *= 2;
		}
		read(fd, &ch, 1);
	}
	buff[chars_read] = ch;
	// printf();
}