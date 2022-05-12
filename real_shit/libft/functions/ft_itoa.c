/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:12:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/12 13:57:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: Replace with ft_strlcpy
static void	string_copy(char *dest, const char *src, int num_chars)
{
	int	i;

	i = 0;
	while (i < num_chars)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

// TODO: Does not pass norminette
char	*ft_itoa(int n)
{
	int		num_copy;
	int		num_digits;
	int		i;
	char	*str;
	int		is_neg;

	num_digits = 0;
	is_neg = 0;
	if (n == -2147483648)
	{
		str = malloc(sizeof(char) * 12);
		if (str == NULL)
			return (NULL);
		string_copy(str, "-2147483648", 11);
		return (str);
	}
	else if (n == 0)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	else if (n < 0)
	{
		n *= -1;
		is_neg = 1;
	}
	num_copy = n;
	while (num_copy > 0)
	{
		num_copy /= 10;
		num_digits++;
	}
	str = malloc(sizeof(char) * (num_digits + is_neg + 1));
	i = num_digits + is_neg - 1;
	while (i >= 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	if (is_neg)
		str[0] = '-';
	str[num_digits + is_neg] = '\0';
	return (str);
}
