/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:53:29 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/15 13:49:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next_node;

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
