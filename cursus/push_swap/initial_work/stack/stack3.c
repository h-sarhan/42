/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:26:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:22:21 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	stack_iter(t_stack *lst, void (*f)(int))
{
	t_stack	*node;

	node = lst;
	while (node != NULL)
	{
		(*f)(node->num);
		node = node->next;
	}
}

t_stack	*stack_map(t_stack *lst, int (*f)(int))
{
	t_stack	*old;
	t_stack	*new;
	int		new_content;
	t_stack	*temp;

	old = lst;
	new = NULL;
	while (old != NULL)
	{
		new_content = (*f)(old->num);
		temp = stack_new(new_content);
		if (temp == NULL)
		{
			stack_clear(&new);
			return (NULL);
		}
		stack_add_bottom(&new, temp);
		old = old->next;
	}
	return (new);
}
