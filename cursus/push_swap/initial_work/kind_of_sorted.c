/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kind_of_sorted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:19:16 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 16:39:03 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	kind_of_sorted_asc(t_stack *stack)
{
	t_stack	*outer_el;
	t_stack	*inner_el;

	int sorted;
	outer_el = stack;
	while (outer_el != NULL)
	{
		sorted = 1;
		inner_el = outer_el;
		while (inner_el->next != outer_el)
		{
			if (inner_el->num > inner_el->next->num)
			{
				sorted = 0;
				break ;
			}
			inner_el = inner_el->next;
			if (inner_el->next == NULL)
				inner_el = stack_top(stack);
		}
		outer_el = outer_el->next;
		if (sorted == 1)
			return (1);
	}
	return (0);
}
