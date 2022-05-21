/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/21 05:01:25 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_conv_params(t_conversion *conv)
{
	printf("Conversion Type: %c\n", conv->type);
	printf("Minimum Width: %d\n", conv->min_width);
	printf("Pad to the right?: %d\n", conv->pad_right);
	printf("Pad zeros?: %d\n", conv->pad_zeros);
	printf("Precision?: %d\n", conv->precision);
	printf("Precision Amount: %u\n", conv->precision_amount);
	printf("Alt Form?: %d\n", conv->alt_form);
	printf("Space?: %d\n", conv->space);
	printf("Sign?: %d\n\n", conv->sign);
}

#include <string.h>
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_conversion	*conv = new_conversion(argv[1]);

	printf("%s\n", argv[1]);
	print_conv_params(conv);

	/*
	int (*pf)(const char *, ...);
	if (argc > 1 && ft_strncmp(argv[1], "real", ft_strlen("real")) == 0)
		pf = &printf;
	else if (argc > 1 && ft_strncmp(argv[1], "mine", ft_strlen("real")) == 0)
		pf = &ft_printf;
	else
		return (0);

	// **Simple mandatory tests**
	
	// Printing characters
	int num_chars = (*pf)("%c%c%c%c%c%c%c", '1', '2', '3', '4', '5', '6', '7');
	(*pf)("\n%d\n", num_chars);

	// Printing strings
	num_chars = (*pf)("%s%s%s", "Germany", "Japan", "Turkey");
	(*pf)("\n%d\n", num_chars);

	// Printing pointers
	void *nums[] = {(void *)123, (void *)0, (void *)2147483647, (void *)(2147483647UL + 20), (void *)4294967295, (void *)(4294967295UL + 20), 0};
	num_chars = (*pf)("%p%p%p%p%p%p%p", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6]);
	(*pf)("\n%d\n", num_chars);

	// Printing ints
	int	ints[] = {12345, -189908, 1000, -1000, 0, 4294967295UL - 20};
	num_chars = (*pf)("%d%d%d%d%d%d", ints[0], ints[1], ints[2], ints[3], ints[4], ints[5]);
	(*pf)("\n%d\n", num_chars);

	num_chars = (*pf)("%i%i%i%i%i%i", ints[0], ints[1], ints[2], ints[3], ints[4], ints[5]);
	(*pf)("\n%d\n", num_chars);

	// Printing unsigned ints
	unsigned int	uints[] = {87657, 1756, 0,  4294967295UL - 20};
	num_chars = (*pf)("%u%u%u%u", uints[0], uints[1], uints[2], uints[3]);
	(*pf)("\n%d\n", num_chars);

	// Printing hexadecimal
	unsigned long	hex[] = {87686, -190198, 0, 4294967295UL - 20, 4294967295UL + 20};
	num_chars = (*pf)("%x%x%x%x%x", hex[0], hex[1], hex[2], hex[3], hex[4]);
	(*pf)("\n%d\n", num_chars);
	
	num_chars = (*pf)("%X%X%X%X%X", hex[0], hex[1], hex[2], hex[3], hex[4]);
	(*pf)("\n%d\n", num_chars);

	// Printing percent
	num_chars = (*pf)("%%%%%%");
	(*pf)("\n%d\n", num_chars);

	// Combination of everything
	num_chars = (*pf)("%d\n %i\n        \t     %p\n\n %X\t%u\n", 1234, 9876, (void*) 17668, 6547, 245678999);
	(*pf)("\n%d\n", num_chars);
	*/
}
