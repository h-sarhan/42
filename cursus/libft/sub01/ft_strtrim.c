/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 22:39:27 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/08 20:26:22 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gen_empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	*str = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed;
	int		i;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) != NULL)
		start++;
	while (ft_strchr(set, s1[end]) != NULL)
		end--;
	if (ft_strlen(s1) == 0 || start > end)
		return (gen_empty_string());
	else
		trimmed = malloc(sizeof(char) * (end - start + 2));
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (i + start <= end)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

// #include <stdio.h>
// int	main()
// {
// 	char	str[] = "    ,,,,,,         hello, nada,,,,,,,    ,,,    , ,, ,,";
	
// 	char* trimmed_str = ft_strtrim(str, ", ");
	
// 	printf("My output:\n|%s|\n", trimmed_str);
// 	printf("Correct output:\n|%s|\n", "hello, nada");
// }