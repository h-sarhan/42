/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:24:48 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/14 22:32:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"


void ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*new_front;
	
	new_front = ft_create_elem(data);
	if (new_front == NULL)
		return ;
	if (*begin_list == NULL)
		*begin_list = new_front;
	else
	{
		new_front->next = *begin_list;
		*begin_list = new_front;
	}
}