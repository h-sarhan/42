/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:54:17 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/01 17:24:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

void	assert_is_null(char *msg, void *result)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (result == NULL)
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
	else
		print_msg_color(CROSS " Test Failed!\n\n", ERROR);
}

void	assert_is_not_null(char *msg, void *result)
{
	print_msg_color(msg, WHITE);
	write(1, "\n", 1);
	if (result != NULL)
		print_msg_color(CHECKMARK " Test Passed!\n\n", SUCCESS);
	else
		print_msg_color(CROSS " Test Failed!\n\n", ERROR);
}
