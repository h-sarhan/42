/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:39:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/02 11:47:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

void	assert_true(char *msg, int result)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (result)
	{
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
	}
	else
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result is False\n\n", ERROR);
	}
}

void	assert_false(char *msg, int result)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (!result)
	{
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
	}
	else
	{
		print_msg_color(CROSS " Test Failed!\n", ERROR);
		print_msg_color("Result is True\n\n", ERROR);
	}
}
