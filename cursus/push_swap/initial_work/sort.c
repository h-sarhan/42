/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:59:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/26 15:45:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min_stack(t_stack *stack, int after)
{
	int	min_idx;
	t_stack	*min_stack;

	min_stack = stack;
	min_idx = stack->final_idx;
	while (stack != NULL)
	{
		if (stack->final_idx < min_idx && stack->final_idx > after)
		{
			min_stack = stack;
			min_idx = stack->final_idx;
		}
		stack = stack->next;
	}
	return (min_stack);
}

void	sort_single_stack(t_stack *stack)
{
	t_stack*	min_stack;
	int			idx;

	idx = 0;
	while (!kind_of_sorted_asc(stack))
	{
		min_stack = find_min_stack(stack, idx);
		idx = min_stack->final_idx;
		
	}
}
