/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:51:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/01 17:31:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

void	assert_int_equal(char *msg, int result, int expected)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (result != expected)
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		write(1, YELLOW "Result=", 12);
		ft_putnbr(result);
		write(1, "\nExpected=", 10);
		ft_putnbr(expected);
		write(1, "\n" RESET, 7);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
}

void	assert_int_array_equal(char *msg, int *result, int *expected, int len)
{
	int	is_equal;
	int	i;

	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	is_equal = 1;
	i = 0;
	while (i < len)
	{
		if (result[i] != expected[i])
			is_equal = 0;
		i++;
	}
	if (!is_equal)
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		write(1, YELLOW "Result Array = ", 20);
		print_int_array(result, len);
		write(1, YELLOW "\nExpected Array = ", 23);
		print_int_array(expected, len);
		write(1, "\n" RESET, 6);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
}

void	assert_int_array_is_sorted(char *msg, int *arr, int len)
{
	int	is_sorted;
	int	i;

	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	is_sorted = 1;
	i = 0;
	while (i < len - 1)
	{
		if (arr[i] > arr[i + 1])
			is_sorted = 0;
		i++;
	}
	if (!is_sorted)
	{
		print_msg_color(CROSS " Test Failed!\nArray is not Sorted!\n", ERROR);
		write(1, YELLOW "Array = ", 13);
		print_int_array(arr, len);
		write(1, "\n" RESET, 6);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\nArray is Sorted\n\n", SUCCESS);
}
