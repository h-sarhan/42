/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:39:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 10:24:32 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

bool	assert_true(char *msg, bool result)
{
	print_msg_color(msg, WHITE);
	if (result)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	else
	{
		if (*msg != '\0')
		{
			print_msg_color(CROSS " Test Failed!\n", ERROR);
			print_msg_color("Result is False\n", ERROR);
		}
		return (false);
	}
}

bool	assert_false(char *msg, bool result)
{
	print_msg_color(msg, WHITE);
	if (!result)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	else
	{
		if (*msg)
		{
			print_msg_color(CROSS " Test Failed!\n", ERROR);
			print_msg_color("Result is True\n", ERROR);
		}
		return (false);
	}
}

bool	assert_bool_array_equal(char *msg, bool *res, bool *expected, int len)
{
	int	is_equal;
	int	i;

	print_msg_color(msg, WHITE);
	is_equal = 1;
	i = 0 - 1;
	while (++i < len)
		if (res[i] != expected[i])
			is_equal = 0;
	if (!is_equal && *msg != '\0')
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result Array = ", YELLOW);
		print_bool_array(res, len, YELLOW);
		print_msg_color("\nExpected Array = ", YELLOW);
		print_bool_array(expected, len, YELLOW);
		write(1, "\n", 1);
	}
	if (!is_equal)
		return (false);
	else if (*msg != '\0')
		print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
	return (true);
}
