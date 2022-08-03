/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:55:52 by hsarhan           #+#    #+#             */
/*   Updated: 2022/08/03 11:29:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"


void	*resize(char **arr, size_t old_len, size_t new_len)
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
	return (new_arr);
}

char	*get_next_line(int fd)
{
	char	ch;
	char	*buff;
	size_t	buff_size;
	size_t	chars_read;
	int		read_return;

	if (fd < 0)
		return (NULL);
	buff_size = 100;
	buff = ft_calloc(buff_size + 1, sizeof(char));
	if (buff == NULL)
		return (NULL);
	chars_read = 0;
	ch = 0;
	read_return = read(fd, &ch, 1);
	if (read_return <= 0)
	{
		free(buff);
		return (NULL);
	}
	while (read_return > 0 && ch != '\n')
	{
		buff[chars_read] = ch;
		chars_read++;
		if (chars_read >= buff_size)
		{
			resize(&buff, buff_size, buff_size * 2);
			buff_size *= 2;
		}
		read_return = read(fd, &ch, 1);
	}
	if (read_return > 0 && ch == '\n')
		buff[chars_read] = ch;
	return (buff);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	int fd = open(argv[1], O_RDONLY);
// 	char *line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// }
