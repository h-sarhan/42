/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:49:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 11:54:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)())
{
	t_list	*lst;
	t_list	*temp;

	lst = *begin_list;
	if (lst == NULL)
	{
		lst = ft_create_elem(data);
		return ;		
	}
	while (lst->next != NULL)
	{
		if (cmp(lst->data, data) < 0 && cmp(lst->next->data, data) > 0)
		{
			temp = lst->next;
			lst->next = ft_create_elem(data);
			lst->next->next = temp;
			return ;
		}
		lst = lst->next;
	}
	lst->next = ft_create_elem(data);
}