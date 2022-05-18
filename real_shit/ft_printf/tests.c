/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/18 23:13:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(int argc, char **argv)
{
	print_hex_int(atoi(argv[1]), UPPER);
	printf("\nOG_PRINTF: %X\n", atoi(argv[1]));
	int	n = 45;
	int *p = &n;
	print_hex_pointer(45);
	write(STDOUT, "\n", 1);
	printf("OG_PRINTF: %p\n", 45);
	
	
	print_hex_int(4294967295 + 20, UPPER);
	printf("\nOG_PRINTF: %X\n", 4294967295 + 20);
	
	print_hex_pointer(4294967295 + 20);
	printf("\nOG_PRINTF: %p\n", 4294967295 + 20);
	
	print_hex_int(0, UPPER);
	printf("\nOG_PRINTF: %X\n", 0);
	
	print_hex_pointer(0);
	printf("\nOG_PRINTF: %p\n", 0);
}
