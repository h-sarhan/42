/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 03:49:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*node;

	node = ft_calloc(1, sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->content = content;
	return (node);
}

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
int		main(){}
