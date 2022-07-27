/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:59:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/27 17:35:19 by hsarhan          ###   ########.fr       */
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
	min_stack = stack;
	min_idx = stack->final_idx;
	// min_idx = -1;
	while (stack != NULL)
	{
		if (stack->final_idx < min_idx && stack->final_idx >= after)
		{
			min_stack = stack;
			min_idx = stack->final_idx;
			found = 1;
		}
		stack = stack->next;
	}
	if (!found)
		return (NULL);
	return (min_stack);
}

void	selection_sort(t_stack **stack)
{

}
