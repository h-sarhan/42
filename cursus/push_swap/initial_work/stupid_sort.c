/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 07:04:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 12:12:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// This will be like selection sort but with push swap operations
// Not intended to be optimal, just creating this to understand push swap
t_stack	*find_min(t_stack *list)
{
	t_stack	*min;

	list = stack_top(list);
	min = list;
	while (list != NULL)
	{
		if (list->num < min->num)
			min = list;
		list = list->next;
	}
	return (min);
}

void	move_to_bottom(t_stack *min)
{
	t_stack	*stack;

	stack = min;
	while (min->next != NULL)
	{
		reverse_rotate(&stack, NULL, 'a');
	}
}

void	move_to_top(t_stack *min)
{
	t_stack	*stack;

	stack = stack_top(min);
	while (min->prev != NULL)
	{
		rotate(&stack, NULL, 'a');
	}
}

void	stupid_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	stacka_size;
	t_stack	*min;

	stacka_size = stack_size(stack_a);
	while (stack_size(stack_b) < stacka_size)
	{
		min = find_min(stack_a);
		move_to_top(min);
		push(&stack_a, &stack_b, 'b');
	}
	while (stack_size(stack_b) > 0)
		push(&stack_a, &stack_b, 'a');
}
