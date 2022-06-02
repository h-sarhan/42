/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:43:45 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/02 22:03:57 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	if (line_buffer == NULL)
	{
		line_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (line_buffer == NULL)
			return (NULL);
		bytes_read = read(fd, line_buffer, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(line_buffer);
			line_buffer = NULL;
			return (NULL);
		}
		line_buffer[bytes_read] = '\0';
	}
	line = extract_line(fd, &line_buffer);
	return (line);
}

int	read_into_buffer(char **buffer, int fd, int chars_read, int *max_size)
{
	int	bytes_read;

	if (chars_read + max(BUFFER_SIZE, 10) >= *max_size)
	{
		*max_size += max(BUFFER_SIZE, 10);
		*buffer = resize(buffer, chars_read, *max_size + 1);
		if (*buffer == NULL)
			return (-1);
	}
	bytes_read = read(fd, &(*buffer)[chars_read], BUFFER_SIZE);
	(*buffer)[chars_read + bytes_read] = '\0';
	return (bytes_read);
}

int	go_to_next_line(int fd, char **line_buffer)
{
	int	i;
	int	max_buffer_size;
	int	bytes_read;

	i = 0;
	max_buffer_size = max(BUFFER_SIZE, ft_strlen(*line_buffer));
	while ((*line_buffer)[i] != '\n')
	{
		if ((*line_buffer)[i] == '\0')
		{
			bytes_read = read_into_buffer(line_buffer, fd, i, &max_buffer_size);
			if (bytes_read == -1)
				return (-1);
			if (bytes_read < BUFFER_SIZE)
			{
				while ((*line_buffer)[i] != '\n' && (*line_buffer)[i] != '\0')
					i++;
				break ;
			}
		}
		else
			i++;
	}
	return (i);
}

char	*create_line(char **line_buffer, int line_length)
{
	char	*line;
	int		i;

	line = malloc(line_length + 1 * sizeof(char));
	if (line == NULL)
	{
		free(*line_buffer);
		return (NULL);
	}
	i = 0;
	while (i < line_length)
	{
		line[i] = (*line_buffer)[i];
		i++;
	}
	line[line_length] = '\0';
	return (line);
}

char	*extract_line(int fd, char **line_buffer)
{
	int		i;
	char	*line;
	int		line_length;

	i = go_to_next_line(fd, line_buffer);
	if (i == -1)
		return (NULL);
	if ((*line_buffer)[0] == '\0')
	{
		free(*line_buffer);
		*line_buffer = NULL;
		return (NULL);
	}
	line_length = i + 1;
	line = create_line(line_buffer, line_length);
	i = 0;
	while ((*line_buffer)[i + line_length] != '\0')
	{
		(*line_buffer)[i] = (*line_buffer)[i + line_length];
		i++;
	}
	(*line_buffer)[i] = '\0';
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	char *line;
// 	int fd = open(argv[1], O_RDONLY);
// 	int	num_lines = atoi(argv[2]);
// 	int i = 0;
// 	while (i < num_lines)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL) 
// 			printf("#%d NULL\n", i + 1);
// 		else
// 		{
// 			printf("#%d %s", i + 1, line);
// 			// printf("%s", line);
// 			free(line);
// 		}
// 		i++;
// 	}
// 	close(fd);
// }