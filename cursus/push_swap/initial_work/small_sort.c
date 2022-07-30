/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 06:33:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 17:17:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **stack_a, t_stack **stack_b)
{
	int	nums[3];

	if (is_sorted_asc(*stack_a))
		return ;
	nums[0] = (*stack_a)->num;
	nums[1] = (*stack_a)->next->num;
	nums[2] = (*stack_a)->next->next->num;
	if (nums[0] > nums[1] && nums[0] < nums[2] && nums[1] < nums[2])
		swap(stack_a, stack_b, 'a');
	else if (nums[0] > nums[1] && nums[0] > nums[2] && nums[1] < nums[2])
		rotate(stack_a, stack_b, 'a', 0);
	else if (nums[0] < nums[1] && nums[0] > nums[2] && nums[1] > nums[2])
		reverse_rotate(stack_a, stack_b, 'a', 0);
	else if (nums[0] > nums[1] && nums[0] > nums[2] && nums[1] > nums[2])
	{
		swap(stack_a, stack_b, 'a');
		reverse_rotate(stack_a, stack_b, 'a', 0);
	}
	else
	{
		swap(stack_a, stack_b, 'a');
		rotate(stack_a, stack_b, 'a', 0);
	}
}

void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	bool	rev;

	rev = false;
	if (forward_dist(stack_a, 0) > reverse_dist(stack_a, 0))
		rev = true;
	while ((*stack_a)->final_idx != 0 && rev)
		reverse_rotate(stack_a, stack_b, 'a', 0);
	while ((*stack_a)->final_idx != 0 && !rev)
		rotate(stack_a, stack_b, 'a', 0);
	if (is_sorted_asc(*stack_a))
		return ;
	push(stack_a, stack_b, 'b');
	sort_three(stack_a, stack_b);
	push(stack_a, stack_b, 'a');
}

void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	bool	rev;

	rev = false;
	if (forward_dist(stack_a, 0) > reverse_dist(stack_a, 0))
		rev = true;
	while ((*stack_a)->final_idx != 0 && rev)
		reverse_rotate(stack_a, stack_b, 'a', 0);
	while ((*stack_a)->final_idx != 0 && !rev)
		rotate(stack_a, stack_b, 'a', 0);
	if (is_sorted_asc(*stack_a))
		return ;
	push(stack_a, stack_b, 'b');
	rev = false;
	if (forward_dist(stack_a, 1) > reverse_dist(stack_a, 1))
		rev = true;
	while ((*stack_a)->final_idx != 1 && rev)
		reverse_rotate(stack_a, stack_b, 'a', 0);
	while ((*stack_a)->final_idx != 1 && !rev)
		rotate(stack_a, stack_b, 'a', 0);
	push(stack_a, stack_b, 'b');
	sort_three(stack_a, stack_b);
	if ((*stack_b)->num < (*stack_b)->next->num)
		swap(stack_a, stack_b, 'b');
	push(stack_a, stack_b, 'a');
	push(stack_a, stack_b, 'a');
}

void	sort_small(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_size(stack_a) == 2 && stack_a->num > stack_a->next->num)
		swap(&stack_a, &stack_b, 'a');
	if (stack_size(stack_a) == 3)
		sort_three(&stack_a, &stack_b);
	if (stack_size(stack_a) == 4)
		sort_four(&stack_a, &stack_b);
	if (stack_size(stack_a) == 5)
		sort_five(&stack_a, &stack_b);
}
