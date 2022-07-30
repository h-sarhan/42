/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 05:23:41 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 16:42:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	push(t_stack **stack_a, t_stack **stack_b, char which)
{
	t_stack	*popped;
	t_stack	*temp;

	if (stack_a == NULL && stack_b == NULL)
		return ;
	if (which == 'a' && stack_size(*stack_b) > 0)
	{
		popped = *stack_b;
		temp = popped->next;
		if (popped->next != NULL)
			popped->next = NULL;
		*stack_b = temp;
		stack_add_top(stack_a, popped);
		ft_printf("pa\n");
	}
	if (which == 'b' && stack_size(*stack_a) > 0)
	{
		popped = *stack_a;
		temp = popped->next;
		if (popped->next != NULL)
			popped->next = NULL;
		*stack_a = temp;
		stack_add_top(stack_b, popped);
		ft_printf("pb\n");
	}
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
// 	stack_print(stack_b);
// 	ft_printf("\n");
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'a');
// 	push(&stack_a, &stack_b, 'b');
// 	push(&stack_a, &stack_b, 'b');
// 	push(&stack_a, &stack_b, 'b');
// 	push(&stack_a, &stack_b, 'b');
// 	push(&stack_a, &stack_b, 'b');
// 	push(&stack_a, &stack_b, 'b');
// 	push(&stack_a, &stack_b, 'a');
// 	ft_printf("\n");
// 	stack_print(stack_a);
// 	stack_print(stack_b);
// }