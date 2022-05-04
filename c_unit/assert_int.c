/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:51:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 10:07:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

bool	assert_int_equal(char *msg, int result, int expected)
{
	print_msg_color(msg, WHITE);
	if (result != expected)
	{
		if (*msg != '\0')
		{
			print_msg_color(CROSS " Test Failed!\n", ERROR);
			print_msg_color("Result=", YELLOW);
			ft_putnbr(result, YELLOW);
			print_msg_color("\nExpected=", YELLOW);
			ft_putnbr(expected, YELLOW);
			write(1, "\n", 1);
		}
		return (false);
	}
	else
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
}

bool	assert_int_array_equal(char *msg, int *result, int *expected, int len)
{
	int	is_equal;
	int	i;

	print_msg_color(msg, WHITE);
	is_equal = 1;
	i = 0 - 1;
	while (++i < len)
		if (result[i] != expected[i])
			is_equal = 0;
	if (!is_equal && *msg != '\0')
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result Array = ", YELLOW);
		print_int_array(result, len, YELLOW);
		print_msg_color("\nExpected Array = ", YELLOW);
		print_int_array(expected, len, YELLOW);
		write(1, "\n", 1);
	}
	if (!is_equal)
		return (false);
	else if (*msg != '\0')
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
	return (true);
}

bool	assert_int_array_is_sorted(char *msg, int *arr, int len)
{
	int	is_sorted;
	int	i;

	print_msg_color(msg, WHITE);
	is_sorted = 1;
	i = 0;
	while (i < len - 1)
	{
		if (arr[i] > arr[i + 1])
			is_sorted = 0;
		i++;
	}
	if (!is_sorted && *msg != '\0')
	{
		print_msg_color(CROSS " Test Failed!\nArray is not Sorted!\n", ERROR);
		print_msg_color("Array = ", YELLOW);
		print_int_array(arr, len, YELLOW);
		write(1, "\n", 1);
	}
	if (!is_sorted)
		return (false);
	else if (*msg != '\0')
		print_msg_color(CHECKMARK " Test Passed!\nArray is Sorted\n", SUCCESS);
	return (true);
}
