/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:26:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/19 21:10:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	stack_size(t_stack *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_stack	*stack_bottom(t_stack *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	get_final_positions(t_stack *stack)
{
	t_stack	*min;
	int		idx;

	idx = 0;
	while (idx < stack_size(stack))
	{
		min = find_min(stack);
		min->final_idx = idx;
		idx++;
	}
	// while(stack != NULL)
	// {
	// 	printf("%d\n", stack->final_idx);
	// 	stack = stack->next;
	// }
}
