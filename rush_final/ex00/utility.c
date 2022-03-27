/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:55:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/27 21:25:50 by mwasef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	is_whitespace(char ch)
{
	if (ch == '\t' || ch == '\n' || ch == '\v'
		|| ch == '\f' || ch == '\r' || ch == ' ')
		return (1);
	return (0);
}

int	get_num_digits(char *str)
{
	int	num_digits;

	num_digits = 0;
	while (*str >= '0' && *str <= '9')
	{
		num_digits++;
		str++;
	}
	return (num_digits);
}

int	power_of_10(int power)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	while (i < power)
	{
		result *= 10;
		i++;
	}
	return (result);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	num;
	int	num_digits;
	int	current_digit;

	sign = 1;
	num = 0;
	current_digit = 0;
	while (is_whitespace(*str))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	num_digits = get_num_digits(str);
	while (current_digit < num_digits)
	{
		num += (*str - '0') * power_of_10(num_digits - 1 - current_digit);
		current_digit++;
		str++;
	}
	return (sign * num);
}

char	read_char_from_file(int file)
{
	char	ch;
	int		bytes_read;

	bytes_read = read(file, &ch, 1);
	if (bytes_read == 0)
		return ('\0');
	return (ch);
}
