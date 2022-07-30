/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 15:50:22 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// TODO: CHECK ERROR MANAGEMENT SECTION
int	main(int argc, char **argv)
{
	// t_stack	*stack_a;
	// t_stack	*stack_b;
	// int chunk_size;
	// int i;
	// char **nums;
	
	// ! TODO: LEAKS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	(void)argc;
	if (argc == 1)
	{
		return (EXIT_SUCCESS);
	}
	char *arg_string = arg_joiner(argv);
	// ft_printf("%s\n", arg_string);
	check_args(arg_string);
	free(arg_string);
	// stack_a = NULL;
	// stack_b = NULL;
	// if (argc > 2)
	// {
	// 	i = 1;
	// 	while (i < argc)
	// 		stack_add_bottom(&stack_a, stack_new(ft_atoi(argv[i++])));
	// }
	// else if (argc == 2)
	// {
	// 	nums = ft_split(argv[1], ' ');
	// 	i = 0;
	// 	while (nums[i] != NULL)
	// 		stack_add_bottom(&stack_a, stack_new(ft_atoi(nums[i++])));
	// }
	// get_final_positions(stack_a);
	// if (is_sorted_asc(stack_a))
	// 	return (0);
	// if (stack_size(stack_a) <= 5)
	// {
	// 	if (stack_size(stack_a) == 2 && stack_a->num > stack_a->next->num)
	// 		swap(&stack_a, &stack_b, 'a');
	// 	if (stack_size(stack_a) == 3)
	// 		sort_three(&stack_a, &stack_b);
	// 	if (stack_size(stack_a) == 4)
	// 		sort_four(&stack_a, &stack_b);
	// 	if (stack_size(stack_a) == 5)
	// 		sort_five(&stack_a, &stack_b);
	// }
	// else
	// {
	// 	chunk_size = 0.1075 * stack_size(stack_a) + 6.25;
	// 	chunk(&stack_a, &stack_b, chunk_size);
	// 	sort_after_chunking(&stack_a, &stack_b);
	// }
}

