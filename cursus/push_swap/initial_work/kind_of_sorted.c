/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kind_of_sorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:19:16 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 14:07:51 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Check if all elements before minimum element are in increasing order.
// Check if all elements after minimum element are in increasing order.
// Check if the last element of the array is smaller than the starting element.
int	kind_of_sorted_asc(t_stack *stack)
{
	t_stack	*min;
	t_stack *bottom;
	t_stack *top;
	
	if (is_sorted_asc(stack))
		return (1);
	top = stack;
	bottom = stack_bottom(stack);
	if (stack_size(stack) < 3)
		return (1);
	min = find_min(stack);
	while (stack != NULL && stack->next != min)
	{
		if (stack->num > stack->next->num)
			return (0);
		stack = stack->next;
	}
	stack = min->next;
	while (stack != NULL && stack->next != NULL)
	{
		if (stack->num > stack->next->num)
			return (0);
		stack = stack->next;
	}
	if (bottom->num < top->num)
		return (1);
	else
		return (0);
}
