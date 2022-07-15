/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 18:10:22 by hsarhan          ###   ########.fr       */
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
	// insertion_sort(&stack_a, &stack_b);
	partition_start(&stack_a, &stack_b);
	// stack_print(stack_a);
	// stack_print(stack_b);
	print_stacks_side_by_side(stack_a, stack_b);
	
	// t_stack    *stack;
	// stack = NULL;
	// int nums[] = {6, 11 , 10, 9, 8 , 7};
	// int i = 0;
	// while (i < sizeof(nums)/sizeof(int))
	// 	stack_add_bottom(&stack, stack_new(nums[i++]));
	// ft_printf("%d\n", kind_of_sorted_desc(stack));
}


// ! 100 ints insertion sort gives me ~3500 moves
// TODO: CHECK ERROR MANAGEMENT SECTION
// PUSH SWAP RANGES:
// 2 integers:
// 2 - 3 moves
// 5 integers:
// 8 - 12 moves
// 100 integers:
// [5 points] less than 700 moves
// [4 points] less than 900 moves
// [3 points] less than 1100 moves
// [2 points] less than 1300 moves
// [1 points] less than 1500 moves
// 500 integers:
// [5 points] less than 5500 moves
// [4 points] less than 7000 moves
// [3 points] less than 8500 moves
// [2 points] less than 10000 moves
// [1 points] less than 11500 moves
