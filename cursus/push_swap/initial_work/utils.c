/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:09:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 14:08:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min(t_stack *stack)
{
	t_stack	*min;
	// t_stack	*top;
	
	// stack = stack;
	min = stack;
	while (stack != NULL)
	{
		if (stack->num < min->num)
			min = stack;
		stack = stack->next;
	}
	return (min);
}

int	is_sorted_desc(t_stack *stack)
{
	while (stack->next != NULL)
	{
		if (stack->num < stack->next->num)
			return (0);
		stack = stack->next;
	}
	return (1);
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

t_stack	*find_max(t_stack *list)
{
	t_stack	*max;

	// list = list;
	max = list;
	while (list != NULL)
	{
		if (list->num > max->num)
			max = list;
		list = list->next;
	}
	return (max);
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