/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 10:47:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Creates a new stack element
t_stack	*stack_new(int num)
{
	t_stack	*node;

	node = ft_calloc(1, sizeof(t_stack));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->num = num;
	node->final_idx = -1;
	return (node);
}

// Adds a stack element to the bottom of the stack
void	stack_add_bottom(t_stack **lst, t_stack *new)
{
	t_stack	*back;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next != NULL)
		back = back->next;
	back->next = new;
}

// Returns the size of a stack
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

// Returns the element at the bottom of a stack
t_stack	*stack_bottom(t_stack *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// Frees a every element of a stack
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
