/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:43:45 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/02 20:31:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*get_next_line(int fd)
{
	static char	*line_buffer[1000];
	char		*line;
	
	if (fd < 0)
		return (NULL);
	line = extract_line(fd, &line_buffer[fd]);
	
	return (line);
}


char	*extract_line(int fd, char **line_buffer)
{
	int		i;
	int		max_buffer_size;
	int		chars_in_buffer;
	int		bytes_read;
	char	*line;
	int		line_length;
	
	i = 0;
	max_buffer_size = BUFFER_SIZE;
	bytes_read = -1;
	chars_in_buffer = 0;
	
	// IF LINE BUFFER IS EMPTY
	// FILL IT AND NULL TERMINATE IT
	// IF BYTES READ is 0 FREE LINE BUFFER AND RETURN NULL
	if (*line_buffer == NULL)
	{
		*line_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (*line_buffer == NULL)
			return (NULL);
		bytes_read = read(fd, *line_buffer, BUFFER_SIZE);
		chars_in_buffer += bytes_read;
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(*line_buffer);
			*line_buffer = NULL;
			return (NULL);
		}
		(*line_buffer)[bytes_read] = '\0';
	}
	// GO THROUGH BUFFER UNTIL WE REACH THE NEXT LINE
	while ((*line_buffer)[i] != '\n')
	{
		// IF WE REACH END OF BUFFER WITHOUT FINDING A NEW LINE
		// RESIZE BUFFER to be NUMBER OF CHARS READ + BUFFER_SIZE + 1 for '\0'
		// READ `BUFFER_SIZE` CHARACTERS INTO THE RESIZED LINE BUFFER
		if ((*line_buffer)[i] == '\0')
		{
			if (chars_in_buffer + max(BUFFER_SIZE, 10) >= max_buffer_size)
			{
				max_buffer_size += max(BUFFER_SIZE, 10);
				*line_buffer = resize(line_buffer, i, max_buffer_size + 1);
				if (*line_buffer == NULL)
					return (NULL);
			}
			bytes_read = read(fd, &(*line_buffer)[i], BUFFER_SIZE);
			chars_in_buffer += bytes_read;
			(*line_buffer)[i + bytes_read] = '\0';
			// If bytes read is less than buffer size
			// we increment i until we reach a new line or the end of the file
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
	if ((*line_buffer)[0] == '\0')
	{
		free(*line_buffer);
		*line_buffer = NULL;
		return (NULL);
	}
	line_length = i + 1;
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