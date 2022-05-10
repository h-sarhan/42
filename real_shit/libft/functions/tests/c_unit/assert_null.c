/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:54:17 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 22:49:09 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

bool	assert_is_null(char *msg, void *result)
{
	print_msg_color(msg, WHITE);
	if (result == NULL)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	return (false);
}

bool	assert_is_not_null(char *msg, void *result)
{
	print_msg_color(msg, WHITE);
	if (result != NULL)
	{
		if (*msg != '\0')
			print_msg_color(CHECKMARK " Test Passed!\n", SUCCESS);
		return (true);
	}
	print_msg_color(CROSS " Test Failed!\n", ERROR);
	return (false);
}
