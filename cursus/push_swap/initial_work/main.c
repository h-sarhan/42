/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 16:40:51 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		chunk_size;
	int		i;

	if (argc == 1)
		return (EXIT_SUCCESS);
	int	num_args;
	char *arg_string = arg_joiner(argv);
	int	*nums = parse_args(arg_string, &num_args);
	free(arg_string);
	stack_a = NULL;
	stack_b = NULL;
	i = 0;
	while (i < num_args)
	{
		t_stack	*stack_el = stack_new(nums[i++]);
		if (stack_el == NULL)
		{
			stack_clear(&stack_a);
			free(nums);
			exit(EXIT_FAILURE);
		}
		stack_add_bottom(&stack_a, stack_el);
	}
	free(nums);
	get_final_positions(stack_a);
	if (is_sorted_asc(stack_a))
	{
		stack_clear(&stack_a);
		return (0);
	}
	if (stack_size(stack_a) <= 5)
	{
		if (stack_size(stack_a) == 2 && stack_a->num > stack_a->next->num)
			swap(&stack_a, &stack_b, 'a');
		if (stack_size(stack_a) == 3)
			sort_three(&stack_a, &stack_b);
		if (stack_size(stack_a) == 4)
			sort_four(&stack_a, &stack_b);
		if (stack_size(stack_a) == 5)
			sort_five(&stack_a, &stack_b);
	}
	else
	{
		chunk_size = 0.1075 * stack_size(stack_a) + 6.25;
		chunk(&stack_a, &stack_b, chunk_size);
		sort_after_chunking(&stack_a, &stack_b);
	}
	stack_clear(&stack_a);
}

