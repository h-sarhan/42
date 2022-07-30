/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 16:59:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fill_stack(t_stack **stack, char **argv)
{
	char	*arg_string;
	int		*nums;
	int		num_args;
	int		i;
	t_stack	*stack_el;

	arg_string = arg_joiner(argv);
	nums = parse_args(arg_string, &num_args);
	free(arg_string);
	i = 0;
	while (i < num_args)
	{
		stack_el = stack_new(nums[i++]);
		if (stack_el == NULL)
		{
			stack_clear(stack);
			free(nums);
			exit(EXIT_FAILURE);
		}
		stack_add_bottom(stack, stack_el);
	}
	free(nums);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		chunk_size;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1)
		return (EXIT_SUCCESS);
	fill_stack(&stack_a, argv);
	get_final_positions(stack_a);
	if (is_sorted_asc(stack_a))
	{
		stack_clear(&stack_a);
		return (0);
	}
	if (stack_size(stack_a) <= 5)
		sort_small(stack_a, stack_b);
	else
	{
		chunk_size = 0.1075 * stack_size(stack_a) + 6.25;
		chunk(&stack_a, &stack_b, chunk_size);
		sort_after_chunking(&stack_a, &stack_b);
	}
	stack_clear(&stack_a);
}
