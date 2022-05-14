/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/14 13:36:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_old;
	t_list	*old;
	t_list	*first_new;
	t_list	*new;

	if (lst == NULL)
		return (NULL);
	first_old = lst;
	old = lst;
	new = ft_lstnew((*f)(old->content));
	first_new = new;
	old = old->next;
	while (old != NULL)
	{
		new->next = ft_lstnew((*f)(old->content));
		new = new->next;
		if (new == NULL)
			return (NULL);
		old = old->next;
	}
	ft_lstclear(&first_old, del);
	return (first_new);
}
