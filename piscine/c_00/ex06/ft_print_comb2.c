/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:43:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/11 15:43:33 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	write_nums(int num1, int num2)
{
	char	num1_chars[2];
	char	num2_chars[2];

	num1_chars[0] = (num1 / 10) + '0';
	num1_chars[1] = (num1 % 10) + '0';
	num2_chars[0] = (num2 / 10) + '0';
	num2_chars[1] = (num2 % 10) + '0';
	write(1, &num1_chars, 2);
	write(1, " ", 1);
	write(1, &num2_chars, 2);
	if (num1 != 98)
	{
		write(1, ", ", 2);
	}
}

void	ft_print_comb2(void)
{
	int	num1;
	int	num2;
	int	num2_start;

	num1 = 0;
	num2_start = 1;
	while (num1 < 99)
	{
		num2 = num2_start;
		while (num2 < 100)
		{
			write_nums(num1, num2);
			num2++;
		}
		num2_start++;
		num1++;
	}
	write(1, "\n", 1);
}

int	main(void)
{
	ft_print_comb2();
}
