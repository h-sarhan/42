/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 12:08:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	// TODO: CHECK FOR DUPLICATES
	// TODO: CHECK FOR OVERFLOW
	// TODO: OTHER STUFF
	t_stack	*stack_a = NULL;
	t_stack	*stack_b = NULL;
	if (argc > 2)
	{
		int i = 1;
		while (i < argc)
			stack_add_bottom(&stack_a, stack_new(ft_atoi(argv[i++])));
	}
	else if (argc == 2)
	{
		char **nums = ft_split(argv[1], ' ');
		int i = 0;
		while (nums[i] != NULL)
			stack_add_bottom(&stack_a, stack_new(ft_atoi(nums[i++])));
	}
	stupid_sort(stack_a, stack_b);
	// stack_print(stack_a);
}
