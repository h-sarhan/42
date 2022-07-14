/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 07:04:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:22:04 by hsarhan          ###   ########.fr       */
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

void	move_to_bottom()
{
	t_stack	*bottom;

	bottom = stack_bottom();
}