/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:13:29 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/19 22:09:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	experiment(t_stack *stack_a)
{
	t_stack	*stack_b = NULL;
	print_stacks_side_by_side(stack_a, stack_b);
	stack_print(stack_a);
	while (1)
	{
		char *line = get_next_line(0);
		if (line == NULL)
			break;
		line = ft_strtrim(line, "\n");
		if (ft_strncmp(line, "ra", ft_strlen(line)) == 0)
			rotate(&stack_a, &stack_b, 'a', 0);
		if (ft_strncmp(line, "rb", ft_strlen(line)) == 0)
			rotate(&stack_a, &stack_b, 'b', 0);
		if (ft_strncmp(line, "rra", ft_strlen(line)) == 0)
			reverse_rotate(&stack_a, &stack_b, 'a', 0);
		if (ft_strncmp(line, "rrb", ft_strlen(line)) == 0)
			reverse_rotate(&stack_a, &stack_b, 'b', 0);
		if (ft_strncmp(line, "pa", ft_strlen(line)) == 0)
			push(&stack_a, &stack_b, 'a');
		if (ft_strncmp(line, "pb", ft_strlen(line)) == 0)
			push(&stack_a, &stack_b, 'b');
		if (ft_strncmp(line, "sa", ft_strlen(line)) == 0)
			swap(&stack_a, &stack_b, 'a');
		if (ft_strncmp(line, "sb", ft_strlen(line)) == 0)
			swap(&stack_a, &stack_b, 'b');
		print_stacks_side_by_side(stack_a, stack_b);
		stack_print(stack_a);
		if (kind_of_sorted_asc(stack_a) && !is_sorted_asc(stack_a))
			ft_printf("THE STACK IS SORTED JUST ROTATE\n");
		else if (is_sorted_asc(stack_a))
			ft_printf("ALLAHU AKBAR\n");
	}
}