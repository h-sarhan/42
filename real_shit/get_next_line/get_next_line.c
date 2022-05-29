/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:43:45 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/29 20:44:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
	static char	*line_buffer = NULL;
	char		*line;
		
	if (line_buffer == NULL)
		line_buffer = malloc(BUFFER_SIZE);
	line = extract_line(fd, line_buffer);
	printf("%s", line);
	return (line_buffer);
}

char	*resize(char *arr, int old_len, int new_len, int term)
{
	int		i;
	char	*new_arr;
	
	i = 0;
	new_arr = malloc(new_len);
	while (i < old_len && i < new_len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	if (term == TRUE)
		new_arr[i] = '\0';
	return (new_arr);
}

char	*extract_line(int fd, char *line_buffer)
{
	int	i;
	int	buffer_len;
	int	bytes_read;

	i = 0;
	bytes_read = 0;
	buffer_len = read(fd, line_buffer, BUFFER_SIZE);
	if (buffer_len < BUFFER_SIZE)
		return (resize(line_buffer, BUFFER_SIZE, bytes_read + 1, TRUE));
	while (line_buffer[i] != '\n')
	{
		if (i == buffer_len)
		{
			line_buffer = resize(line_buffer, buffer_len, buffer_len * 2, FALSE);
			bytes_read = read(fd, &line_buffer[i], BUFFER_SIZE);
			if (bytes_read < BUFFER_SIZE)
				return (resize(line_buffer, buffer_len, buffer_len + bytes_read + 1, TRUE));
			buffer_len += bytes_read;
		}
		i++;
	}
	return (resize(line_buffer, buffer_len, i + 2, TRUE));
}

int	main(int argc, char **argv)
{
	char ch;
	int fd = open(argv[1], O_RDONLY);
	int	num_lines = atoi(argv[2]);
	int i = 0;
	while (i < num_lines)
	{
		get_next_line(fd);
		i++;
	}
	close(fd);
}