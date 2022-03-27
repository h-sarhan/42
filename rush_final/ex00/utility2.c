/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:38:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/27 21:26:00 by mwasef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

int	get_num_digits_from_int(int num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		num_digits++;
	}
	return (num_digits);
}

void	put_word(char *str, int add_space)
{
	if (add_space == 1)
		write(1, " ", 1);
	while (*str != '\0')
	{
		write(1, str, 1);
		str++;
	}
}

char	*trim_whitespace(char *line, int val_index)
{
	char	*trimmed_str;
	int		val_start;
	int		val_end;
	int		line_length;
	int		val_idx;

	line_length = ft_strlen(line);
	val_start = val_index + 1;
	while (line[val_start] == ' ' && val_start < line_length)
		val_start++;
	val_end = ft_strlen(line) - 1;
	while ((line[val_end] == ' ' || line[val_end] == '\n')
		&& val_end > val_start)
		val_end--;
	if (val_start >= val_end || val_start >= line_length)
		return (NULL);
	trimmed_str = malloc(sizeof(char) * (val_end - val_start + 2));
	val_idx = 0;
	while (val_start + val_idx < val_end + 1)
	{
		trimmed_str[val_idx] = line[val_start + val_idx];
		val_idx++;
	}
	trimmed_str[val_idx] = '\0';
	return (trimmed_str);
}
