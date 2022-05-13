/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/13 18:43:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_old;
	t_list	*old;
	t_list	*first_new;
	t_list	*new;
	void	*new_content;

	first_old = lst;
	old = lst;
	new = NULL;
	while (old != NULL)
	{
		new_content = (*f)(old->content);
		if (new == NULL)
		{
			new = ft_lstnew(new_content);
			first_new = new;
		}
		else
		{
			new->next = ft_lstnew(new_content);
			new = new->next;
		}
		if (new == NULL)
			return (NULL);
		old = old->next;
	}
	ft_lstclear(&first_old, del);
	return (first_new);
}
