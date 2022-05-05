/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:37:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/05 23:07:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit/c_unit.h"
#include "ft_putnbr.h"
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int	main(int argc, char **argv)
{
	if (argc == 1 || test_util_strcmp(argv[1], "c") == 0)
	{
	}
	else if (test_util_strcmp(argv[1], "expected") == 0)
	{
		char ch;
		for (ch = 1; ch < 127; ch++)
			if (isprint(ch))
				printf("%c\n", ch);
		int	i;
		for (i = INT_MIN; i < INT_MIN + 100; i++)
			printf("%d\n", i);
		for (i = INT_MAX - 100; i < INT_MAX; i++)
			printf("%d\n", i);
		for (i = -1000; i < 1000; i++)
			printf("%d\n", i);
	}
	else if (test_util_strcmp(argv[1], "actual") == 0)
	{
		char ch;
		for (ch = 1; ch < 127; ch++)
			if (isprint(ch))
			{
				ft_putchar(ch);
				ft_putchar('\n');
			}
		int	i;
		for (i = INT_MIN; i < INT_MIN + 100; i++)
		{
			ft_putnbr(i);
			write(1, "\n", 1);
		}
		for (i = INT_MAX - 100; i < INT_MAX; i++)
		{
			ft_putnbr(i);
			write(1, "\n", 1);
		}
		for (i = -1000; i < 1000; i++)
		{
			ft_putnbr(i);
			write(1, "\n", 1);
		}
	}
}
