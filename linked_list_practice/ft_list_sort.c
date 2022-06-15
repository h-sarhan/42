/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 10:38:50 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 11:07:26 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_list.h"

void print_int(void *p);

t_list	*min_element(t_list **begin, int (*cmp)())
{
	unsigned int	i;
	t_list			*el;
	t_list			*min;
	
	el = *begin;
	min = el;
	i = 0;
	while (el != NULL)
	{
		if (cmp(el->data, min->data) < 0)
			min = el;
		i++;
		el = el->next;
	}
	return (min);
}

void	swap_list(t_list *l1, t_list *l2)
{
	void	*temp;

	temp = l1->data;
	l1->data = l2->data;
	l2->data = temp;
}


void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*el;
	t_list	*min;

	el = *begin_list;
	while (el != NULL)
	{
		min = min_element(&el, cmp);
		swap_list(el, min);
		el = el->next;
	}
}