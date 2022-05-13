/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:01:09 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/13 13:47:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char sep)
{
	int	i;
	int	num_words;

	i = 0;
	num_words = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sep && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		num_words++;
		while (str[i] != sep && str[i] != '\0')
			i++;
	}
	return (num_words);
}

// TODO: DOES NOT PASS NORMINETTE
char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		word_start;
	int		word_end;
	int		word_count;

	words = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		word_start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		word_end = i - 1;
		words[word_count] = malloc(sizeof(char) * (word_end - word_start + 2));
		if (words[word_count] == NULL)
			return (NULL);
		ft_strlcpy(words[word_count], &s[word_start],
			word_end - word_start + 2);
		word_count++;
	}
	words[word_count] = NULL;
	return (words);
}
