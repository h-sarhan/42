/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:33:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 10:35:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	if (*begin_list1 == NULL)
		*begin_list1 = begin_list2;
	else
		ft_list_last(*begin_list1)->next = begin_list2;
}
