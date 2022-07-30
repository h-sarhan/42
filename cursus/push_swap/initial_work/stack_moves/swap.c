/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:47:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 16:51:13 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	swap_a(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	first = *stack_a;
	second = first->next;
	third = second->next;
	first->next = third;
	second->next = first;
	*stack_a = second;
}

static void	swap_b(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	first = *stack_b;
	second = first->next;
	third = second->next;
	first->next = third;
	second->next = first;
	*stack_b = second;
}

void	swap(t_stack **stack_a, t_stack **stack_b, char which)
{
	if ((which == 'a' || which == 'c') && stack_size(*stack_a) > 1)
	{
		swap_a(stack_a);
		if (which != 'c')
			ft_printf("sa\n");
	}
	if ((which == 'b' || which == 'c') && stack_size(*stack_b) > 1)
	{
		swap_b(stack_b);
		if (which != 'c')
			ft_printf("sb\n");
	}
	if (which == 'c')
		ft_printf("ss\n");
}
