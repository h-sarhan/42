/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/19 12:59:09 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(int argc, char **argv)
{
	print_hex_int(atoi(argv[1]), UPPER);
	printf("\nOG_PRINTF: %X\n", atoi(argv[1]));
	int	n = 45;
	int *p = &n;
	print_hex_pointer((void *)45);
	write(STDOUT, "\n", 1);
	printf("OG_PRINTF: %p\n", (void *)45);
	
	
	print_hex_int((unsigned int)4294967295 + 20, UPPER);
	printf("\nOG_PRINTF: %X\n", (unsigned int)4294967295 + 20);
	
	print_hex_pointer((void *)4294967295 + 20);
	printf("\nOG_PRINTF: %p\n", (void *)4294967295 + 20);
	
	print_hex_int(0, UPPER);
	printf("\nOG_PRINTF: %X\n", 0);
	
	print_hex_pointer((void *)0);
	printf("\nOG_PRINTF: %p\n", (void *)0);


	int res1 = ft_printf("i = %d\nj = %d\nptr = %p\nmarks = %d%%\n", 12, 42, p, 48);
	ft_printf("%%");
	ft_printf("\n");
	int exp1 = printf("i = %d\nj = %d\nptr = %p\nmarks = %d%%\n", 12, 42, p, 48);
	printf("%%");
	printf("\n");
	printf("res = %d\nexpected = %d\n", res1, exp1);
}
