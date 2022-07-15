/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:23:41 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 11:55:40 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_stack **stack_a, t_stack **stack_b, char which)
{
	t_stack	*popped;
	t_stack	*temp;

	if (stack_a == NULL || stack_b == NULL)
		return ;
	if (which == 'a' && stack_size(*stack_b) > 0)
	{
		popped = *stack_b;
		temp = popped->next;
		if (popped->next != NULL)
		{
			popped->next = NULL;
		}
		*stack_b = temp;
		stack_add_top(stack_a, popped);
	}
	if (which == 'b' && stack_size(*stack_a) > 0)
	{
		popped = *stack_a;
		temp = popped->next;
		if (popped->next != NULL)
		{
			popped->next = NULL;
		}
		*stack_a = temp;
		stack_add_top(stack_b, popped);
	}
	if (which == 'a')
		ft_printf("pa\n");
	if (which == 'b')
		ft_printf("pb\n");
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