/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:53:26 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/01 17:32:32 by hsarhan          ###   ########.fr       */
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
		write(1, "\n\n", 2);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
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
		write(1, "\n\n", 2);
		write(1, RESET, 1);
	}
	else
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
}
