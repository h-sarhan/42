/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:26:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:22:13 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	stack_size(t_stack *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
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

t_stack	*stack_top(t_stack *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

void	stack_delone(t_stack *lst)
{
	if (lst != NULL)
	{
		free(lst);
	}
}

void	stack_clear(t_stack **lst)
{
	t_stack	*node;
	t_stack	*next_node;

	node = *lst;
	while (node != NULL)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	*lst = NULL;
}
