/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 12:05:27 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_conv_params(t_conversion *conv, void *val)
{
	printf("Conversion Type: %c\n", conv->type);
	printf("Minimum Width: %d\n", conv->min_width);
	printf("Pad to the right?: %d\n", conv->pad_right);
	printf("Pad zeros?: %d\n", conv->pad_zeros);
	printf("Precision?: %d\n", conv->precision);
	printf("Precision Amount: %u\n", conv->precision_amount);
	calculate_padding(conv, val);
	printf("Min Width Padding: %u\n", conv->mw_padding);
	printf("Precision Padding: %u\n", conv->pr_padding);
	printf("Alt Form?: %d\n", conv->alt_form);
	printf("Space?: %d\n", conv->space);
	printf("Sign?: %d\n\n", conv->sign);
}

#include <string.h>
int	main(int argc, char **argv)
{
	int		(*pf)(const char *, ...);
	
	if (argc > 1 && ft_strncmp(argv[1], "expected", 100) == 0)
		pf = printf;
	else
		pf = ft_printf;
	//pf("%010d\n", -10);
	// char *str = "21-school.ru";
	
	char *conv_str = "%-10.x";
	char *str = "us";
	int num = 0;
	print_conv_params(new_conversion(conv_str), &num);
	// print_conv_params(new_conversion(conv_str), &str);
	int ret = pf(conv_str, num);
	// int ret = pf(conv_str, str);
	pf("\n%d\n", ret);
	// char *str = "-";
	// print_conv_params(new_conversion("%.s"), &str);
	//print_conv_params(new_conversion("%.2d"), &num);
	//pf(" %.2d \n", 1);
	//// basic chars
	//char ch = 0;
	//while (ch < 127)
	//{
	//	pf("%c\n", ch);
	//	ch++;
	//}

	//// basic strings
	//char	*str = "adsfsvdsfds";
	//pf("%s\n", str);

	//// basic pointers
	//long i = 0;	
	//while (i < 10000)
	//{
	//	pf("%p\n", (void *)i);
	//	i++;
	//}

	//// basic ints
	//pf("%d\n", 42);
	//pf("%d\n", -42);
	//pf("%d\n", INT_MIN);
	//pf("%d\n", INT_MIN + 100);
	//pf("%d\n", 0);
	//
	//pf("%i\n", 42);
	//pf("%i\n", -42);
	//pf("%i\n", INT_MIN);
	//pf("%i\n", INT_MIN + 100);
	//pf("%i\n", 0);

	//// basic unsigned 
	//pf("%u\n", 87698897);
	//pf("%u\n", 11213);
	//pf("%u\n", 1231);
	//pf("%u\n", -1987);
	//pf("%u\n", 8769876);

	//// basic hexadecimal
	//unsigned int hex_int = 0;
	//while (hex_int < 10000)
	//{
	//	pf("%x\n", hex_int);
	//	pf("%X\n", hex_int);
	//	hex_int++;
	//}

	//// percent sign
	//pf("%%\n");

	//// intense percent sign
	//pf("%% %%%%%%%% %%\n");

	//// combinations
	//pf("%d %d %d %u %X\n", 1213, 1987, -112, 1871, 876587);


	// hard tests
	// // TODO: PRINT '-' before zero padding HARD
//	pf("%04d\n", -14);
//
	// // TODO: FIGURE OUT PRECISION WITH STRING CONVERSION
	// pf("%.1s\n", "");
	// pf("%.s\n", "-");
	// pf("%.2s\n", "");
	// pf("%.3s\n", "4");
	// char *str = "4";
	// print_conv_params(new_conversion("%.3s"), &str);
	// ret = pf(" %.s \n", "-");
	// pf("ret = %d\n", ret);
	// ret  = pf(" %.2s %.1s \n", "", "-");
	// pf("ret = %d\n", ret);
	// ret = pf(" %.3s %.2s \n", " - ", "");
	// pf("ret = %d\n", ret);
	// ret = pf(" %.1s %.2s %.3s %.4s \n", " - ", "", "4", "");
	// pf("ret = %d\n", ret);
	// ret = pf(" %.2s %.3s %.4s %.5s %.1s \n", " - ", "", "4", "", "2 ");
	// pf("ret = %d\n", ret);
	// DONE: FIGURE OUT PRECISION WITH NEGATIVE NUMBERS
	// t_conversion	*conv = new_conversion("%-4x");
	// print_conv_params(conv);
	// write(STDOUT, "\n", 1);
	// print_int_conversion(conv, -1);
	// printf("\n");
	// int ret;
	// pf("%.2d\n", -1);
	// ret = pf("%.2d\n", -1);
	// printf("%d\n", ret);
	

// DONE: - with hex
	// print_hex(9, 'x');
	// print_hex_int(9, 'x');
	// write(1, "\n", 1);
	// pf("%-4x\n", 9);
	// unsigned int num = 9;
	// t_conversion *conv = new_conversion("%-4x");
	// printf("init_chrs: %d\n", count_initial_chars(conv, &num));
	// print_conv_params(conv);
	// printf("Count hex output: %d\n", count_hex(num));
	// write(1, "|", 1);
	// pf("%-4x\n", 9);
	// pf("%-1x\n", 10);
	//print_hex_conversion(conv, (unsigned int)9);
	// print_conv_params(conv);
	// ft_printf("%-1x\n", 10);

	// DONE: FIX '#' RETURN VALUE
//	ret = pf(" %#x \n", 1);
//	printf("%d\n", ret);

	// DONE: FIX SPACE WITH NEGATIVE NUMBERS RETURN VALUE
	//ret = pf(" % d \n", -9);
	
	// DONE: FIX PLUS WITH NEGATIVE NUMBERS RETURN VALUE
//	ret = pf(" %+d\n", -10);
//	printf("%d\n", ret);
}
