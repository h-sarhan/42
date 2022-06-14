/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:24:48 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/14 22:45:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"


void ft_list_push_back(t_list **begin_list, void *data)
{
	t_list	*back;
	
	back = ft_create_elem(data);
	if (back == NULL)
		return ;
	if (*begin_list == NULL)
		*begin_list = back;
	else
		ft_list_last(*begin_list)->next = back;
}