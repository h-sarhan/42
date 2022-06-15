/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:10:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 11:13:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_reverse_fun(t_list *begin_list)
{
	unsigned int	start;
	unsigned int	end;

	start = 0;
	end = ft_list_size(begin_list) - 1;
	while (start < end)
	{
		swap_list(ft_list_at(begin_list, start), ft_list_at(begin_list, end));
		start++;
		end--;
	}
}