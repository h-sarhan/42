/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:23:41 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 05:46:45 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_dlist **stack_a, t_dlist **stack_b, char which)
{
	t_dlist	*popped;
	t_dlist	*temp;

	if (stack_a == NULL || stack_b == NULL)
		return ;
	if (which == 'a' && ft_dlstsize(*stack_b) > 0)
	{
		popped = ft_dlstfirst(*stack_b);
		temp = popped->next;
		temp->prev = NULL;
		*stack_b = temp;
		ft_dlstadd_front(stack_a, temp);
	}
	if (which == 'b' && ft_dlstsize(*stack_a) > 0)
	{
		popped = ft_dlstfirst(*stack_a);
		temp = popped->next;
		temp->prev = NULL;
		*stack_b = temp;
		ft_dlstadd_front(stack_b, temp);
	}
}