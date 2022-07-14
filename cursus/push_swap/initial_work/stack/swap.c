/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:47:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 05:05:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_dlist **stack_a, t_dlist **stack_b, char which)
{
	t_dlist	*first;
	t_dlist	*second;
	t_dlist	*third;

	if ((which == 'a' || which == 's') && stack_a != NULL)
	{
		if (ft_dlstsize(*stack_a) > 1)
		{
			first = ft_dlstfirst(*stack_a);
			second = first->next;
			third = second->next;
			second->prev = NULL;
			second->next = first;
			first->prev = second;
			first->next = third;
			third->prev = first;
			*stack_a = second;
		}
	}
	if ((which == 'b' || which == 's') && stack_b != NULL)
	{
		if (ft_dlstsize(*stack_b) > 1)
		{
			first = ft_dlstfirst(*stack_b);
			second = first->next;
			third = second->next;
			second->prev = NULL;
			second->next = first;
			first->prev = second;
			first->next = third;
			third->prev = first;
			*stack_b = second;
		}
	}
	if (which == 'a')
		ft_printf("sa\n");
	if (which == 'b')
		ft_printf("sb\n");
	if (which == 's')
		ft_printf("ss\n");
}

int	main()
{
	int	nums[] = {10, 20, 30, 40, 50};
	t_dlist	*list = NULL;
	int i = 0;
	while (i < 5)
	{
		ft_dlstadd_back(&list, ft_dlstnew(&nums[i]));
		i++;
	}
	ft_dlst_print_ints(list);
	swap(&list, NULL, 'a');
	ft_dlst_print_ints(list);
}