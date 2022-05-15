/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:53:55 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 23:03:31 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"

void	print_int_array(int *arr, int arr_len, char *color)
{
	int	idx;

	idx = 0;
	print_msg_color("[", color);
	while (idx < arr_len - 1)
	{
		test_util_putnbr(arr[idx], color);
		print_msg_color(", ", color);
		idx++;
	}
	test_util_putnbr(arr[idx], color);
	print_msg_color("]\n", color);
}

void	print_str_array(char **arr, int arr_len, char *color)
{
	int	idx;

	idx = 0;
	print_msg_color("[", color);
	while (idx < arr_len - 1)
	{
		print_msg_color(arr[idx], color);
		print_msg_color(", ", color);
		idx++;
	}
	print_msg_color(arr[idx], color);
	print_msg_color("]\n", color);
}

void	print_bool_array(bool *arr, int arr_len, char *color)
{
	int	idx;

	idx = 0;
	print_msg_color("[", color);
	while (idx < arr_len - 1)
	{
		if (arr[idx] == true)
			print_msg_color("true", color);
		else
			print_msg_color("false", color);
		print_msg_color(", ", color);
		idx++;
	}
	if (arr[idx] == true)
		print_msg_color("true", color);
	else
		print_msg_color("false", color);
	print_msg_color("]\n", color);
}

void	print_msg_color(char *msg, char *color)
{
	write(1, color, 5);
	while (*msg != '\0')
	{
		write(1, msg, 1);
		msg++;
	}
	write(1, RESET, 5);
}
