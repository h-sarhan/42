/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:23:41 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 05:54:11 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_dlist **stack_a, t_dlist **stack_b, char which)
{
	t_dlist	*popped;
	t_dlist	*temp;

	if (stack_a == NULL || stack_b == NULL)
		return ;
	if (which == 'a' && ft_dlstsize(*stack_b) > 0)
	{
		popped = ft_dlstfirst(*stack_b);
		temp = popped->next;
		temp->prev = NULL;
		*stack_b = temp;
		ft_dlstadd_front(stack_a, popped);
	}
	if (which == 'b' && ft_dlstsize(*stack_a) > 0)
	{
		popped = ft_dlstfirst(*stack_a);
		temp = popped->next;
		temp->prev = NULL;
		*stack_a = temp;
		ft_dlstadd_front(stack_b, popped);
	}
}

// int	main()
// {
// 	int	nums[] = {10, 20, 30, 40, 50};
// 	int	nums2[] = {60, 70, 80, 90, 100};
// 	t_dlist	*list = NULL;
// 	t_dlist	*list2 = NULL;
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		ft_dlstadd_back(&list, ft_dlstnew(nums[i]));
// 		ft_dlstadd_back(&list2, ft_dlstnew(nums2[i]));
// 		i++;
// 	}
// 	ft_dlst_print(list);
// 	ft_dlst_print(list2);
// 	ft_printf("\n");
// 	push(&list, &list2, 'b');
// 	ft_dlst_print(list);
// 	ft_dlst_print(list2);
// }