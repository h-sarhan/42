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

static int	skip_to_end_quote(const char *str, char quote);

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

static int	skip_to_end_quote(const char *str, char quote)
{
	int	i;
	int	end;

	i = 1;
	end = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			end = i;
		i++;
	}
	return (end);
}

static char	*create_word(char const *str, int start, int end)
{
	char	*word;

	word = ft_calloc(end - start + 2, sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_strlcpy(word, &str[start], end - start + 2);
	return (word);
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
		if (s[i] == '\'' || s[i] == '\"')
			i += skip_to_end_quote(&s[i], s[i]);
		while (s[i] != c && s[i] != '\0')
			i++;
		words[wc] = create_word(s, word_start, i - 1);
		malloc_check(words[wc++]);
	}
	words[wc] = NULL;
	return (words);
}
