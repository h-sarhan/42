/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:43:45 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 14:22:48 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line_buffer = NULL;
	char		*line;
		
	line = extract_line(fd, &line_buffer);
	
	return (line);
}

void	resize(char **arr, int old_len, int new_len, int term)
{
	int		i;
	char	*new_arr;
	
	i = 0;
	new_arr = malloc(new_len);
	while (i < old_len && i < new_len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	if (term == TRUE)
		new_arr[i] = '\0';
	*arr = new_arr;
}
#include <strings.h>

char	*extract_line(int fd, char **line_buffer)
{
	int		i;
	int		buffer_len;
	int		bytes_read;
	char	*line;
	int		line_length;
	
	i = 0;
	buffer_len = 0;
	bytes_read = -1;
	// printf("LINE BUFFER IS == |%s| \n", *line_buffer);
	
	// IF LINE BUFFFER IS EMPTY
	// FILL IT AND NULL TERMINATE IT
	// IF BYTES READ is 0 FREE LINE BUFFER AND RETURN NULL
	if (*line_buffer == NULL)
	{
		*line_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		bytes_read = read(fd, *line_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
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
			resize(line_buffer, i, (i + 1) + BUFFER_SIZE + 1, TRUE);
			bytes_read = read(fd, &(*line_buffer)[i], BUFFER_SIZE);
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
	// IF LINE BUFERR IS 
	if ((*line_buffer)[i] == '\0')
	{
		free(*line_buffer);
		*line_buffer = NULL;
		return (NULL);
	}
	line_length = i + 1;
	line = malloc(sizeof(char) * (line_length + 1));
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
	while ((*line_buffer)[i] != '\0')
	{
		(*line_buffer)[i] = '\0';
		i++;
	}
	return (line);
}

int	main(int argc, char **argv)
{
	char *line;
	int fd = open(argv[1], O_RDONLY);
	int	num_lines = atoi(argv[2]);
	int i = 0;
	while (i < num_lines)
	{
		line = get_next_line(fd);
		if (line == NULL) 
			printf("#%d NULL\n", i + 1);
		else
		{
			printf("#%d %s", i + 1, line);
			// printf("%s", line);
			free(line);
		}
		i++;
	}
	close(fd);
}