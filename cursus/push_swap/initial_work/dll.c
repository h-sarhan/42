/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:04:46 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 04:07:57 by hsarhan          ###   ########.fr       */
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
	(*lst)->prev = new;
	new->next = *lst;
	*lst = new;
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*back;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = *lst;
	while (back->next != NULL)
		back = back->next;
	back->next = new;
	new->prev = back;
}

void	ft_dlstprintints(t_dlist *lst)
{
	while (lst != NULL)
	{
		ft_printf("%d\n", *(int *)lst->content);
		lst = lst->next;
	}
}

int		main()
{
	int	nums[] = {-10, 10, 20, 30, 40, 50};
	t_dlist	*list = NULL;
	int i = 0;
	while (i < 6)
	{
		ft_dlstadd_back(&list, ft_dlstnew(&nums[i]));
		i++;
	}
	ft_dlstprintints(list);
}
