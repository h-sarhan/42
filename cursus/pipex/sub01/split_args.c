/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:47:32 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/21 22:46:21 by hsarhan          ###   ########.fr       */
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
		if (str[i] == '\\' && ft_strchr("\"\'\\", str[i + 1]))
			i += 2;
		else
			i++;
		num_chars++;
	}
	return (num_chars);
}

// Escapes quotes in a string
static char	*escape_quotes(char *str)
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
		if (str[i] == '\\' && ft_strchr("\"\'\\", str[i + 1]))
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

// Increments i until we reach the end quote
static int	skip_to_end_quote(const char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote && str[i - 1] != '\\')
			break ;
		i++;
	}
	return (i);
}

// Counts the arguments in a string
static int	count_args(char const *str, char sep)
{
	int	i;
	int	num_words;

	i = 0;
	num_words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep && str[i] != '\'' && str[i] != '\"')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i += skip_to_end_quote(&str[i], str[i]);
		if (str[i] == '\0')
			break ;
		num_words++;
		while (str[i] != sep && str[i] != '\0')
			i++;
	}
	return (num_words);
}

// Same as ft_split except that we always treat whatever is inside
// quotation marks as one word
char	**split_args(char const *s, char c)
{
	char	**words;
	int		i;
	int		word_start;
	int		wc;

	words = ft_calloc(count_args(s, c) + 1, sizeof(char *));
	malloc_check(words);
	i = 0;
	wc = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\'' && s[i] != '\"')
			i++;
		if (s[i] == '\0')
			break ;
		word_start = i;
		if ((s[i] == '\'' || s[i] == '\"') && (i == 0 || s[i - 1] != '\\'))
			i += skip_to_end_quote(&s[i], s[i]);
		while (s[i] != c && s[i] != '\0')
			i++;
		words[wc] = escape_quotes(ft_substr(s, word_start, i - word_start));
		malloc_check(words[wc++]);
	}
	words[wc] = NULL;
	return (words);
}
