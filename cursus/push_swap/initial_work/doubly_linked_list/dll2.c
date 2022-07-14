/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:26:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 05:44:34 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_dlstsize(t_dlist *lst)
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

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

void	ft_dlstdelone(t_dlist *lst)
{
	if (lst != NULL)
	{
		free(lst);
	}
}

void	ft_dlstclear(t_dlist **lst)
{
	t_dlist	*node;
	t_dlist	*next_node;

	node = *lst;
	while (node != NULL)
	{
		next_node = node->next;
		free(node);
		node = next_node;
	}
	*lst = NULL;
}
