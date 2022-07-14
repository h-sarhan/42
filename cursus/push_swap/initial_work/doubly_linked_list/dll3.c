/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:26:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 05:45:25 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_dlstiter(t_dlist *lst, void (*f)(int))
{
	t_dlist	*node;

	node = lst;
	while (node != NULL)
	{
		(*f)(node->num);
		node = node->next;
	}
}

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(int))
{
	t_dlist	*old;
	t_dlist	*new;
	void	*new_content;
	t_dlist	*temp;

	old = lst;
	new = NULL;
	while (old != NULL)
	{
		new_content = (*f)(old->num);
		temp = ft_dlstnew(new_content);
		if (temp == NULL)
		{
			ft_dlstclear(&new);
			return (NULL);
		}
		ft_dlstadd_back(&new, temp);
		old = old->next;
	}
	return (new);
}
