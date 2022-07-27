/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/27 17:11:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min_stack_after(t_stack *stack, int after);
// /usr/bin/python3 python_visualizer.py `ruby -e "puts (0..100).to_a.shuffle.join(' ')"`
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
	get_final_positions(stack_a);

	// t_stack* min_stack = find_min_stack_after(stack_a, 5);
	// printf("MIN STACK AFTER %d\n", min_stack->num);
	int chunk_size = 15;

	// chunk(&stack_a, &stack_b, chunk_size);

	selection_sort(&stack_a);
	// sort_after_chunking(&stack_a, &stack_b, chunk_size);

	// print_stacks_side_by_side(stack_a, NULL);
}

// TODO: CHECK ERROR MANAGEMENT SECTION
// ! 100 ints with 15 chunk size ~650
// ! 500 ints with 60 chunk size ~5570
// PUSH SWAP RANGES:
// 2 integers:
// 2 - 3 moves
// 5 integers:
// 8 - 12 moves
// 100 integers:
//? [5 points] less than 700 moves
// [4 points] less than 900 moves
// [3 points] less than 1100 moves
// [2 points] less than 1300 moves
// [1 points] less than 1500 moves
// 500 integers:
// [5 points] less than 5500 moves
//? [4 points] less than 7000 moves
// [3 points] less than 8500 moves
// [2 points] less than 10000 moves
// [1 points] less than 11500 moves
