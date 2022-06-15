/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 09:51:29 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 10:02:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list	*left;
	t_list	*right;
	t_list	*next;
	
	if (*begin_list == NULL || (*begin_list)->next == NULL)
		return ;
	left = NULL;
	right = *begin_list;
	next = right->next;
	while (next != NULL)
	{
		right->next = left;
		left = right;
		right = next;
		next = next->next;
	}
	right->next = left;
	*begin_list = right;
}
