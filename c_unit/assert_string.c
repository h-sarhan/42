/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:53:26 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 23:04:40 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

bool	assert_str_equal(char *msg, char *result, char *expected)
{
	print_msg_color(msg, WHITE);
	if (test_util_strcmp(result, expected) == 0)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	print_msg_color("Result = ", YELLOW);
	print_msg_color(result, YELLOW);
	write(1, "\n", 1);
	print_msg_color("Expected = ", YELLOW);
	print_msg_color(expected, YELLOW);
	write(1, "\n", 2);
	return (false);
}

bool	assert_char_equal(char *msg, char result, char expected)
{
	print_msg_color(msg, WHITE);
	if (result == expected)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	print_msg_color("Result = ", YELLOW);
	write(1, YELLOW, 5);
	write(1, &result, 1);
	print_msg_color("\nExpected = ", YELLOW);
	write(1, YELLOW, 5);
	write(1, &expected, 1);
	write(1, "\n" RESET, 6);
	return (false);
}

bool	assert_str_array_equal(char *msg, char **res, char **expected, int len)
{
	bool	is_equal;
	int		i;

	print_msg_color(msg, WHITE);
	is_equal = true;
	i = 0 - 1;
	while (++i < len)
		if (test_util_strcmp(res[i], expected[i]) != 0)
			is_equal = false;
	if (is_equal)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	print_msg_color("Result Array = ", YELLOW);
	print_str_array(res, len, YELLOW);
	print_msg_color("\nExpected Array = ", YELLOW);
	print_str_array(expected, len, YELLOW);
	write(1, "\n", 1);
	return (false);
}

bool	assert_str_array_is_sorted(char *msg, char **arr, int arr_len)
{
	bool	is_sorted;
	int		i;

	print_msg_color(msg, WHITE);
	is_sorted = true;
	i = 0 - 1;
	while (++i < arr_len - 1)
		if (test_util_strcmp(arr[i], arr[i + 1]) > 0)
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
	print_str_array(arr, arr_len, YELLOW);
	write(1, "\n", 1);
	return (false);
}
