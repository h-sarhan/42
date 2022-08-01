/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:23:41 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 14:59:59 by hsarhan          ###   ########.fr       */
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

static void	push_a(t_stack **stack_a, t_stack **stack_b, bool quiet)
{
	t_stack	*popped;
	t_stack	*temp;

	popped = *stack_b;
	temp = popped->next;
	if (popped->next != NULL)
		popped->next = NULL;
	*stack_b = temp;
	stack_add_top(stack_a, popped);
	if (!quiet)
		ft_printf("pa\n");
}

static void	push_b(t_stack **stack_a, t_stack **stack_b, bool quiet)
{
	t_stack	*popped;
	t_stack	*temp;

	popped = *stack_a;
	temp = popped->next;
	if (popped->next != NULL)
		popped->next = NULL;
	*stack_a = temp;
	stack_add_top(stack_b, popped);
	if (!quiet)
		ft_printf("pb\n");
}

void	push(t_stack **stack_a, t_stack **stack_b, char which, bool quiet)
{
	if (stack_a == NULL && stack_b == NULL)
		return ;
	if (which == 'a' && stack_size(*stack_b) > 0)
		push_a(stack_a, stack_b, quiet);
	if (which == 'b' && stack_size(*stack_a) > 0)
		push_b(stack_a, stack_b, quiet);
}
