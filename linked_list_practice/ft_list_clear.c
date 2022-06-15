/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:26:27 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 09:33:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *))
{
	t_list	*list;
	t_list	*temp;
	
	list = begin_list;
	while (list != NULL)
	{
		temp = list;
		free_fct(list->data);
		list = list->next;
		free(temp);
	}
}
