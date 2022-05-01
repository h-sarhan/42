/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:33:59 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/27 21:25:10 by mwasef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		ft_atoi(char *str);
int		ft_strlen(char *str);
char	*trim_whitespace(char *line, int val_index);
char	read_char_from_file(int file);

char	*get_value(char *line, int line_length)
{
	int		line_idx;

	line_idx = 0;
	while (line[line_idx] != ':' && line_idx < line_length)
		line_idx++;
	return (trim_whitespace(line, line_idx));
}

char	*read_line(char *buffer, int line_start, int line_end)
{
	char	*line;
	int		line_idx;

	if (line_end - line_start <= 1)
		return (NULL);
	line = malloc(sizeof(char) * (line_end - line_start + 2));
	line_idx = 0;
	while (line_idx < line_end - line_start + 1)
	{
		line[line_idx] = buffer[line_start + line_idx];
		line_idx++;
	}
	line[line_idx] = '\0';
	return (line);
}

char	*search_line(int to_find, char *buffer, int line_start, int line_end)
{
	char	*line;
	int		key;
	char	*value;

	line = read_line(buffer, line_start, line_end);
	value = NULL;
	if (line != NULL)
	{
		key = ft_atoi(line);
		if (to_find == key)
		{	
			value = get_value(line, line_end - line_start + 1);
			if (value == NULL)
				write(1, "Dict Error\n", 11);
		}
		free(line);
	}
	return (value);
}

char	*create_buffer(char *file_name)
{
	int		num_chars;
	int		file;
	char	*buffer;
	int		buffer_idx;
	char	ch;

	num_chars = 0;
	file = open(file_name, O_RDONLY);
	while (num_chars == 0 || ch != '\0')
	{
		ch = read_char_from_file(file);
		num_chars++;
	}
	buffer = malloc(sizeof(char) * (num_chars + 1));
	close(file);
	file = open(file_name, O_RDONLY);
	buffer_idx = 0;
	while (buffer_idx < num_chars)
	{
		buffer[buffer_idx] = read_char_from_file(file);
		buffer_idx++;
	}
	buffer[buffer_idx] = '\0';
	close(file);
	return (buffer);
}

char	*search_dictionary(int to_find_key, char *buffer)
{
	int		line_start;
	int		buffer_idx;
	char	*value;

	buffer_idx = 0;
	line_start = 0;
	while (buffer[buffer_idx] != '\0')
	{
		if (buffer[buffer_idx] == '\n')
		{
			value = search_line(to_find_key, buffer, line_start, buffer_idx);
			if (value != NULL)
				return (value);
			line_start = buffer_idx + 1;
		}
		buffer_idx++;
	}
	return (NULL);
}
