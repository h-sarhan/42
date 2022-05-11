/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:02:24 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/17 17:41:02 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	str_length(char *str)
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

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (*s1 != '\0' && *s2 != '\0' && count < n)
	{
		if (*s1 > *s2)
			return (1);
		if (*s1 < *s2)
			return (-1);
		count++;
		s1++;
		s2++;
	}
	if (count == n)
		return (0);
	if (*s1 != '\0')
		return (1);
	if (*s2 != '\0')
		return (-1);
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	unsigned int		to_find_len;
	unsigned int		str_len;
	unsigned int		count;
	char				*search_ptr;

	to_find_len = str_length(to_find);
	if (to_find_len == 0)
		return (str);
	str_len = str_length(str);
	count = 0;
	search_ptr = str;
	while (count < str_len)
	{
		if (ft_strncmp(search_ptr, to_find, to_find_len) == 0)
			return (search_ptr);
		search_ptr++;
		count++;
	}
	return (0);
}
