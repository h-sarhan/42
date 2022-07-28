/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:59:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/28 13:36:26 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min_stack(t_stack *stack)
{
	int	min_idx;
	t_stack	*min_stack;

	min_stack = stack;
	min_idx = stack->final_idx;
	while (stack != NULL)
	{
		if (stack->final_idx < min_idx)
		{
			min_stack = stack;
			min_idx = stack->final_idx;
		}
		stack = stack->next;
	}
	return (min_stack);
}

t_stack	*find_min_stack_after(t_stack *stack, int after)
{
	int	min_idx;
	t_stack	*min_stack;
	int	found;
	
	found = 0;
	while (stack != NULL && stack->final_idx <= after )
		stack = stack->next;
	if (stack == NULL)
		return (NULL);
	min_stack = stack;
	min_idx = stack->final_idx;
	// min_idx = -1;
	while (stack != NULL)
	{
		// printf("AFTER == %d\n", after);
		// stack_print(stack);
		if (stack->final_idx < min_idx && stack->final_idx > after)
		{
			min_stack = stack;
			min_idx = stack->final_idx;
			// found = 1;
		}
		stack = stack->next;
	}
	// if (!found)
	// 	return (NULL);
	return (min_stack);
}



void	selection_sort(t_stack **stack)
{
	t_stack	*prev_min;
	t_stack	*curr_min;

	int rev = 0;
	curr_min = find_min_stack(*stack);
	if (which_direction(stack, curr_min->final_idx) == 1)
		rev = 1;
	else
		rev = 0;
	if (rev == 1)
	{
		while (*stack != curr_min)
			reverse_rotate(stack, NULL, 'a', 0);
	}
	else
	{
		while (*stack != curr_min)
			rotate(stack, NULL, 'a', 0);
	}
	prev_min = curr_min;
	curr_min = find_min_stack_after(*stack, curr_min->final_idx);
	while (curr_min != NULL)
	{
		if (which_direction(stack, curr_min->final_idx) == 1)
			rev = 1;
		else
			rev = 0;
		if (rev == 1)
		{
			while (*stack != curr_min)
				reverse_rotate(stack, NULL, 'a', 0);
		}
		else
		{
			while (*stack != curr_min)
				rotate(stack, NULL, 'a', 0);
		}
		if (which_direction(stack, prev_min->final_idx) == 1)
			rev = 1;
		else
			rev = 0;
		if (rev == 1)
		{
			while (stack_bottom(*stack) != prev_min)
			{
				reverse_rotate(stack, NULL, 'a', 0);
				swap(stack, NULL, 'a');
			}
		}
		else
		{
			while (stack_bottom(*stack) != prev_min)
			{
				swap(stack, NULL, 'a');
				rotate(stack, NULL, 'a', 0);
			}
		}
		prev_min = curr_min;
		curr_min = find_min_stack_after(*stack, curr_min->final_idx);
	}
	rotate(stack, NULL, 'a', 0);
	// stack_print(*stack);
}
