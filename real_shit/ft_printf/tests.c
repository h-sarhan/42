/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/19 15:53:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(int argc, char **argv)
{
	if (argc > 1 && ft_strncmp(argv[1], "real", ft_strlen("real")) == 0)
	{
		// Printing characters
		int num_chars = printf("%c%c%c%c%c%c%c", '1', '2', '3', '4', '5', '6', '7');
		printf("\n%d\n", num_chars);

		// Printing strings
		num_chars = printf("%s%s%s", "Germany", "Japan", "Turkey");
		printf("\n%d\n", num_chars);

		// Printing pointers
		unsigned long nums[] = {123, 0, 2147483647, 2147483647UL + 20, 4294967295, 4294967295UL + 20};
		num_chars = printf("%p%p%p%p%p%p", (void*)nums[0], (void*)nums[1], (void*)nums[2], (void*)nums[3], (void*)nums[4], (void*)nums[5]);
		printf("\n%d\n", num_chars);
	}
	else if (argc > 1 && ft_strncmp(argv[1], "mine", ft_strlen("mine")) == 0)
	{
		int num_chars = ft_printf("%c%c%c%c%c%c%c", '1', '2', '3', '4', '5', '6', '7');
		ft_printf("\n%d\n", num_chars);

		num_chars = ft_printf("%s%s%s", "Germany", "Japan", "Turkey");
		ft_printf("\n%d\n", num_chars);
		
		unsigned long nums[] = {123, 0, 2147483647, 2147483647UL + 20, 4294967295UL, 4294967295UL + 20};
		num_chars = ft_printf("%p%p%p%p%p%p", (void*)nums[0], (void*)nums[1], (void*)nums[2], (void*)nums[3], (void*)nums[4], (void*)nums[5]);
		ft_printf("\n%d\n", num_chars);

	}
}
