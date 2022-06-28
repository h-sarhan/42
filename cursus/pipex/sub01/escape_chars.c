/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:56:20 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/28 13:57:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Counts characters that wont be escaped
static int	count_chars(char *str)
{
	int		i;
	int		num_chars;

	i = 0;
	num_chars = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			i += 2;
		else
			i++;
		num_chars++;
	}
	return (num_chars);
}

// Escapes characters in a string
char	*escape_str(char *str)
{
	int		i;
	char	*escaped_str;
	int		j;

	escaped_str = ft_calloc(count_chars(str) + 1, sizeof(char));
	malloc_check(escaped_str);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			escaped_str[j++] = str[i + 1];
			i += 2;
		}
		else
			escaped_str[j++] = str[i++];
	}
	free(str);
	return (escaped_str);
}
