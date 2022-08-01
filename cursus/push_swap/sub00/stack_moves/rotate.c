/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:58:36 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 12:59:36 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	rotate_a(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*second;

	first = *stack_a;
	second = first->next;
	stack_bottom(*stack_a)->next = first;
	first->next = NULL;
	*stack_a = second;
}

static void	rotate_b(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*second;

	first = *stack_b;
	second = first->next;
	stack_bottom(*stack_b)->next = first;
	first->next = NULL;
	*stack_b = second;
}

void	rotate(t_stack **stack_a, t_stack **stack_b, char which, bool q)
{
	if (stack_a == NULL && stack_b == NULL)
		return ;
	if ((which == 'a' || which == 'c') && stack_size(*stack_a) > 1)
		rotate_a(stack_a);
	if ((which == 'b' || which == 'c') && stack_size(*stack_b) > 1)
		rotate_b(stack_b);
	if (which == 'a' && !q)
		ft_printf("ra\n");
	if (which == 'b' && !q)
		ft_printf("rb\n");
	if (which == 'c' && !q)
		ft_printf("rr\n");
}
