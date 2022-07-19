/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:59:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/19 19:56:27 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// ! SHIT ALGORITHM
void	bubble_sort_stack(t_stack **stack, char which)
{
	while (!kind_of_sorted_asc(*stack))
	{
		t_stack *bottom = stack_bottom(*stack);
		while (*stack != bottom)
		{
			if ((*stack)->num > (*stack)->next->num)
			{
				if (which == 'a')
				{
					swap(stack, NULL, 'a');
					rotate(stack, NULL, 'a');
				}
			}
			else if (which == 'a')
				rotate(stack, NULL, 'a');
			// stack = stack->next;
		}
		// stack = stack->next;
	}
	while (kind_of_sorted_asc(*stack) && !is_sorted_asc(*stack))
		rotate(stack, NULL, which);
}