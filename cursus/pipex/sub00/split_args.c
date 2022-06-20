/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:47:32 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 13:19:03 by hsarhan          ###   ########.fr       */
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

	i = 1;
	while (str[i] != quote && str[i] != '\0')
		i++;
	return (i);
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

char	**split_args(char const *s, char c)
{
	char	**words;
	int		i;
	int		word_start;
	int		wc;

	words = ft_calloc(count_args(s, c) + 1, sizeof(char *));
	if (words == NULL)
		return (NULL);
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
		if (words[wc++] == NULL)
			return (NULL);
	}
	words[wc] = NULL;
	return (words);
}

// int	main()
// { 
// 	char **args  = split_args("wc \"word1 word2\" word3", ' ');
// 	// ft_printf("%d\n", count_args("     kuygkuygb    iluhulyh    \'\"jhgvjhgvgh    \"\'   ", ' '));
// 	ft_printf("%s\n", args[0]);
// 	ft_printf("%s\n", args[1]);
// 	ft_printf("%s\n", args[2]);
// 	ft_printf("%s\n", args[3]);
// }