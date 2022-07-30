/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:09:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 11:38:34 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min(t_stack *stack)
{
	int		min;
	t_stack	*min_stack;

	min = INT_MAX;
	min_stack = stack;
	while (stack != NULL)
	{
		if (stack->num < min)
		{
			min = stack->num;
			min_stack = stack;
		}
		stack = stack->next;
	}
	return (min_stack);
}

int	is_sorted_asc(t_stack *stack)
{
	if (stack_size(stack) < 2)
		return (1);
	while (stack->next != NULL)
	{
		if (stack->num > stack->next->num)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static t_stack	*find_min_pos(t_stack *stack)
{
	int		min;
	t_stack	*min_stack;

	min = INT_MAX;
	min_stack = stack;
	while (stack != NULL)
	{
		if (stack->num < min && stack->final_idx == -1)
		{
			min = stack->num;
			min_stack = stack;
		}
		stack = stack->next;
	}
	return (min_stack);
}

void	get_final_positions(t_stack *stack)
{
	t_stack	*min;
	int		idx;

	idx = 0;
	while (idx < stack_size(stack))
	{
		min = find_min_pos(stack);
		min->final_idx = idx;
		idx++;
	}
}
