/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:29:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 11:30:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	reverse_rotate(t_stack **stack_a, t_stack **stack_b, char which)
{
	t_stack	*first;
	t_stack	*last;
	t_stack	*temp;

	if (stack_a == NULL && stack_b == NULL)
		return ;
	if ((which == 'a' || which == 'c') && stack_size(*stack_a) > 1)
	{
		first = stack_top(*stack_a);
		last = stack_bottom(*stack_a);
		temp = last->prev;
		temp->next = NULL;
		last->next = first;
		last->prev = NULL;
		first->prev = last;
		*stack_a = last;
	}
	if ((which == 'b' || which == 'c') && stack_size(*stack_b) > 1)
	{
		first = stack_top(*stack_b);
		last = stack_bottom(*stack_b);
		temp = last->prev;
		temp->next = NULL;
		last->next = first;
		last->prev = NULL;
		first->prev = last;
		*stack_b = last;
	}
	if (which == 'a')
		ft_printf("rra\n");
	if (which == 'b')
		ft_printf("rrb\n");
	if (which == 'c')
		ft_printf("rrr\n");
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
// 	// ft_dlst_print(list2);
// 	ft_printf("\n");
// 	reverse_rotate(&list, &list2, 'a');
// 	ft_dlst_print(list);
// 	// ft_dlst_print(list2);
// }
