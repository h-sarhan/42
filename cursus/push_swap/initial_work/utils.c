/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:09:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 13:42:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

	list = stack_top(list);
	max = list;
	while (list != NULL)
	{
		if (list->num > max->num)
			max = list;
		list = list->next;
	}
	return (max);
}
