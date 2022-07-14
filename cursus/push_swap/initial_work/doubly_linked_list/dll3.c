/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:26:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 04:28:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*node;
	t_dlist	*next_node;

	node = *lst;
	while (node != NULL)
	{
		next_node = node->next;
		(*del)(node->content);
		free(node);
		node = next_node;
	}
	*lst = NULL;
}

void	ft_dlstiter(t_dlist *lst, void (*f)(void *))
{
	t_dlist	*node;

	node = lst;
	while (node != NULL)
	{
		(*f)(node->content);
		node = node->next;
	}
}

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*old;
	t_dlist	*new;
	void	*new_content;
	t_dlist	*temp;

	old = lst;
	new = NULL;
	while (old != NULL)
	{
		new_content = (*f)(old->content);
		temp = ft_dlstnew(new_content);
		if (temp == NULL)
		{
			(*del)(new_content);
			ft_dlstclear(&new, del);
			return (NULL);
		}
		ft_dlstadd_back(&new, temp);
		old = old->next;
	}
	return (new);
}
