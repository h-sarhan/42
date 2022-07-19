/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:58:36 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/19 21:54:48 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rotate(t_stack **stack_a, t_stack **stack_b, char which, int q)
{
	t_stack	*first;
	t_stack	*second;

	if (stack_a == NULL && stack_b == NULL)
		return ;
	if ((which == 'a' || which == 'c') && stack_size(*stack_a) > 1)
	{
		first = *stack_a;
		second = first->next;
		stack_bottom(*stack_a)->next = first;
		first->next = NULL;
		*stack_a = second;
	}
	if ((which == 'b' || which == 'c') && stack_size(*stack_b) > 1)
	{
		first = *stack_b;
		second = first->next;
		stack_bottom(*stack_b)->next = first;
		first->next = NULL;
		*stack_b = second;
	}
	if (which == 'a' && !q)
		ft_printf("ra\n");
	if (which == 'b' && !q)
		ft_printf("rb\n");
	if (which == 'c' && !q)
		ft_printf("rr\n");
}

// int	main()
// {
// 	int	nums[] = {10, 20, 30, 40, 50};
// 	int	nums2[] = {60, 70, 80, 90, 100};
// 	t_stack	*stack_a = NULL;
// 	t_stack	*stack_b = NULL;
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		stack_add_bottom(&stack_a, stack_new(nums[i]));
// 		stack_add_bottom(&stack_b, stack_new(nums2[i]));
// 		i++;
// 	}
// 	stack_print(stack_a);
// 	// stack_print(stack_b);
// 	rotate(&stack_a, &stack_b, 'a');
// 	rotate(&stack_a, &stack_b, 'a');
// 	rotate(&stack_a, &stack_b, 'a');
// 	rotate(&stack_a, &stack_b, 'a');
// 	rotate(&stack_a, &stack_b, 'a');
// 	rotate(&stack_a, &stack_b, 'a');
// 	ft_printf("\n");
// 	stack_print(stack_a);
// 	// stack_print(stack_b);
// }
