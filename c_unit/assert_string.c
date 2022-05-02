/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:53:26 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/02 16:51:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

void	assert_str_equal(char *msg, char *result, char *expected)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (ft_strcmp(result, expected) != 0)
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result = ", YELLOW);
		print_msg_color(result, YELLOW);
		write(1, "\n", 1);
		print_msg_color("Expected = ", YELLOW);
		print_msg_color(expected, YELLOW);
		write(1, "\n", 2);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
}

void	assert_char_equal(char *msg, char result, char expected)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (result != expected)
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result = ", YELLOW);
		write(1, YELLOW, 5);
		write(1, &result, 1);
		print_msg_color("\nExpected = ", YELLOW);
		write(1, YELLOW, 5);
		write(1, &expected, 1);
		write(1, "\n" RESET, 7);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
}

void	assert_str_array_equal(char *msg, char **res, char **expected, int len)
{
	int	is_equal;
	int	i;

	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	is_equal = 1;
	i = 0;
	while (i < len)
	{
		if (ft_strcmp(res[i], expected[i]) != 0)
			is_equal = 0;
		i++;
	}
	if (!is_equal)
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result Array = ", YELLOW);
		print_str_array(res, len, YELLOW);
		print_msg_color("\nExpected Array = ", YELLOW);
		print_str_array(expected, len, YELLOW);
		write(1, "\n", 1);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
}

void	assert_str_array_is_sorted(char *msg, char **arr, int arr_len)
{
	int	is_sorted;
	int	i;

	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	is_sorted = 1;
	i = 0;
	while (i < arr_len - 1)
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			is_sorted = 0;
		i++;
	}
	if (!is_sorted)
	{
		print_msg_color(CROSS " Test Failed!\nArray is not Sorted!\n", ERROR);
		print_msg_color("Array = ", YELLOW);
		print_str_array(arr, arr_len, YELLOW);
		write(1, "\n", 1);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\nArray is Sorted\n", SUCCESS);
}
