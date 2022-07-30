/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:23:41 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 17:04:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	stack_add_top(t_stack **lst, t_stack *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	push(t_stack **stack_a, t_stack **stack_b, char which)
{
	t_stack	*popped;
	t_stack	*temp;

	if (stack_a == NULL && stack_b == NULL)
		return ;
	if (which == 'a' && stack_size(*stack_b) > 0)
	{
		popped = *stack_b;
		temp = popped->next;
		if (popped->next != NULL)
			popped->next = NULL;
		*stack_b = temp;
		stack_add_top(stack_a, popped);
		ft_printf("pa\n");
	}
	if (which == 'b' && stack_size(*stack_a) > 0)
	{
		popped = *stack_a;
		temp = popped->next;
		if (popped->next != NULL)
			popped->next = NULL;
		*stack_a = temp;
		stack_add_top(stack_b, popped);
		ft_printf("pb\n");
	}
}
