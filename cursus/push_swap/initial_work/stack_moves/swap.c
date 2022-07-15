/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 04:47:33 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 13:07:26 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap(t_stack **stack_a, t_stack **stack_b, char which)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if ((which == 'a' || which == 'c') && stack_size(*stack_a) > 1)
	{
		first = *stack_a;
		second = first->next;
		third = second->next;
		first->next = third;
		second->next = first;
		*stack_a = second;
		if (which != 'c')
			ft_printf("sa\n");
	}
	if ((which == 'b' || which == 'c') && stack_size(*stack_b) > 1)
	{
		first = *stack_b;
		second = first->next;
		third = second->next;
		first->next = third;
		second->next = first;
		*stack_b = second;
		if (which != 'c')
			ft_printf("sb\n");
	}
	if (which == 'c')
		ft_printf("ss\n");
}

// int	main()
// {
// 	int	nums[] = {10, 20, };
// 	int	nums2[] = {60, 70};
// 	t_stack	*stack_a = NULL;
// 	t_stack	*stack_b = NULL;
// 	int i = 0;
// 	while (i < 2)
// 	{
// 		stack_add_bottom(&stack_a, stack_new(nums[i]));
// 		stack_add_bottom(&stack_b, stack_new(nums2[i]));
// 		i++;
// 	}
// 	stack_print(stack_a);
// 	stack_print(stack_b);
// 	swap(&stack_a, &stack_b, 'a');
// 	swap(&stack_a, &stack_b, 'b');
// 	swap(&stack_a, &stack_b, 'c');
// 	ft_printf("\n");
// 	stack_print(stack_a);
// 	stack_print(stack_b);
// }