/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:58:36 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 06:58:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_dlist **stack_a, t_dlist **stack_b, char which)
{
	t_dlist	*first;
	t_dlist	*last;
	t_dlist	*temp;

	if (stack_a == NULL || stack_b == NULL)
		return ;
	if ((which == 'a' || which == 'c') && ft_dlstsize(*stack_a) > 1)
	{
		first = ft_dlstfirst(*stack_a);
		last = ft_dlstlast(*stack_a);
		temp = first->next;
		temp->prev = NULL;
		first->prev = last;
		first->next = NULL;
		last->next = first;
		*stack_a = temp;
	}
	if ((which == 'b' || which == 'c') && ft_dlstsize(*stack_b) > 1)
	{
		first = ft_dlstfirst(*stack_b);
		last = ft_dlstlast(*stack_b);
		temp = first->next;
		temp->prev = NULL;
		first->prev = last;
		first->next = NULL;
		last->next = first;
		*stack_b = temp;
	}
	if (which == 'a')
		ft_printf("ra\n");
	if (which == 'b')
		ft_printf("rb\n");
	if (which == 'c')
		ft_printf("rr\n");
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
// 	// ft_dlst_print(list);
// 	ft_dlst_print(list2);
// 	ft_printf("\n");
// 	rotate(&list, &list2, 'b');
// 	// ft_dlst_print(list);
// 	ft_dlst_print(list2);
// }
