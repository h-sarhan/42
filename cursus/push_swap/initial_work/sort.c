/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:59:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/27 14:15:30 by hsarhan          ###   ########.fr       */
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

// void	sort_single_stack(t_stack **stack)
// {
// 	t_stack*	min_stack;
// 	int			idx;

// }
