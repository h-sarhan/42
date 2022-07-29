/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 07:04:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/29 11:41:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// This will be like selection sort but with push swap operations
// Not intended to be optimal, just creating this to understand push swap




// void	move_to_top(t_stack *min)
// {
// 	t_stack	*stack;

// 	stack = stack_top(min);
// 	while (min->prev != NULL)
// 	{
// 		rotate(&stack, NULL, 'a');
// 	}
// }

// void	stupid_sort(t_stack *stack_a, t_stack *stack_b)
// {
// 	int	stacka_size;
// 	t_stack	*min;

// 	stacka_size = stack_size(stack_a);
// 	while (stack_size(stack_b) < stacka_size)
// 	{
// 		min = find_min_pos(stack_a);
// 		// move_to_top(min);
// 		push(&stack_a, &stack_b, 'b');
// 	}
// 	while (stack_size(stack_b) > 0)
// 		push(&stack_a, &stack_b, 'a');
// }
