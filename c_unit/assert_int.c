/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:51:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/02 16:51:16 by hsarhan          ###   ########.fr       */
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
		print_msg_color("Result=", YELLOW);
		ft_putnbr(result, YELLOW);
		print_msg_color("\nExpected=", YELLOW);
		ft_putnbr(expected, YELLOW);
		write(1, "\n", 1);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
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
		print_msg_color("Result Array = ", YELLOW);
		print_int_array(result, len, YELLOW);
		print_msg_color("\nExpected Array = ", YELLOW);
		print_int_array(expected, len, YELLOW);
		write(1, "\n", 1);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
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
		print_msg_color("Array = ", YELLOW);
		print_int_array(arr, len, YELLOW);
		write(1, "\n", 1);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\nArray is Sorted\n", SUCCESS);
}
