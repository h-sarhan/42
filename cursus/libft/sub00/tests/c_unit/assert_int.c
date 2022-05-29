/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:51:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/12 20:23:23 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

bool	assert_int_equal(char *msg, int result, int expected)
{
	print_msg_color(msg, WHITE);
	if (result == expected)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	print_msg_color("Result=", YELLOW);
	test_util_putnbr(result, YELLOW);
	print_msg_color("\nExpected=", YELLOW);
	test_util_putnbr(expected, YELLOW);
	write(1, RESET "\n", 6);
	return (false);
}

bool	assert_int_array_equal(char *msg, int *result, int *expected, int len)
{
	bool	is_equal;
	int		i;

	print_msg_color(msg, WHITE);
	is_equal = true;
	i = 0 - 1;
	while (++i < len)
		if (result[i] != expected[i])
			is_equal = false;
	if (is_equal)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	print_msg_color("Result Array = ", YELLOW);
	print_int_array(result, len, YELLOW);
	print_msg_color("\nExpected Array = ", YELLOW);
	print_int_array(expected, len, YELLOW);
	write(1, "\n", 1);
	return (false);
}

bool	assert_int_array_is_sorted(char *msg, int *arr, int len)
{
	bool	is_sorted;
	int		i;

	print_msg_color(msg, WHITE);
	is_sorted = true;
	i = 0 - 1;
	while (++i < len - 1)
		if (arr[i] > arr[i + 1])
			is_sorted = false;
	if (is_sorted)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\nArray is Sorted\n",
				SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\nArray is not Sorted!\n", ERROR);
	print_msg_color("Array = ", YELLOW);
	print_int_array(arr, len, YELLOW);
	write(1, "\n", 1);
	return (false);
}
