/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:47:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 19:27:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_stack **stack_a, t_stack **stack_b, char which)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if ((which == 'a' || which == 'c') && stack_a != NULL)
	{
		if (stack_size(*stack_a) > 1)
		{
			first = stack_top(*stack_a);
			second = first->next;
			third = second->next;
			second->prev = NULL;
			second->next = first;
			first->prev = second;
			first->next = third;
			third->prev = first;
			*stack_a = second;
		}
		if (stack_size(*stack_a) == 2)
		{
			first = stack_top(*stack_a);
			second = first->next;
			second->prev = NULL;
			second->next = first;
			first->prev = second;
			first->next = NULL;
			*stack_a = second;
		}
	}
	if ((which == 'b' || which == 'c') && stack_b != NULL)
	{
		if (stack_size(*stack_b) > 1)
		{
			first = stack_top(*stack_b);
			second = first->next;
			third = second->next;
			second->prev = NULL;
			second->next = first;
			first->prev = second;
			first->next = third;
			third->prev = first;
			*stack_b = second;
		}
		if (stack_size(*stack_b) == 2)
		{
			first = stack_top(*stack_b);
			second = first->next;
			second->prev = NULL;
			second->next = first;
			first->prev = second;
			first->next = NULL;
			*stack_b = second;
		}
	}
	if (which == 'a')
		ft_printf("sa\n");
	if (which == 'b')
		ft_printf("sb\n");
	if (which == 'c')
		ft_printf("ss\n");
}
