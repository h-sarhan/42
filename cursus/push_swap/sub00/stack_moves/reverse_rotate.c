/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:29:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 16:50:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	reverse_rotate_a(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*bottom;
	t_stack	*before_bottom;

	first = *stack_a;
	bottom = stack_bottom(*stack_a);
	before_bottom = first;
	while (before_bottom->next->next != NULL)
		before_bottom = before_bottom->next;
	bottom->next = first;
	before_bottom->next = NULL;
	*stack_a = bottom;
}

static void	reverse_rotate_b(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*bottom;
	t_stack	*before_bottom;

	first = *stack_b;
	bottom = stack_bottom(*stack_b);
	before_bottom = first;
	while (before_bottom->next->next != NULL)
		before_bottom = before_bottom->next;
	bottom->next = first;
	before_bottom->next = NULL;
	*stack_b = bottom;
}

void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char which, bool q)
{
	if (stack_a == NULL && stack_b == NULL)
		return ;
	if ((which == 'a' || which == 'c') && stack_size(*stack_a) > 1)
		reverse_rotate_a(stack_a);
	if ((which == 'b' || which == 'c') && stack_size(*stack_b) > 1)
		reverse_rotate_b(stack_b);
	if (which == 'a' && !q)
		ft_printf("rra\n");
	if (which == 'b' && !q)
		ft_printf("rrb\n");
	if (which == 'c' && !q)
		ft_printf("rrr\n");
}
