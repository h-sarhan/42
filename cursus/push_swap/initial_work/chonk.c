/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chonk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/19 21:18:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


// USE THIS EXAMPLE
// 17 0 20 28 11 21 41 12 6 1 46 18 2 43 45 50 29 4 32 23
void	chonk(t_stack **stack_a, t_stack **stack_b, int chonk_size)
{
	int	chonk_idx;

	chonk_idx = 0;
	while (stack_size(*stack_a) > 0)
	{
		if ((*stack_a)->final_idx >= chonk_idx * chonk_size && (*stack_a)->final_idx < (chonk_idx + 1) * chonk_size)
			push(stack_a, stack_b, 'b');
		else
			rotate(stack_a, stack_b, 'a');
		// print_stacks_side_by_side(*stack_a, *stack_b);
		if (stack_size(*stack_b) == (chonk_idx + 1) * chonk_size)
			chonk_idx++;
	}
}


void	sort_after_chonking(t_stack **stack_a, t_stack **stack_b, int chonk_size)
{
	int	next_idx;
	int	curr_idx;
	int	stop_at;

	next_idx = stack_size(*stack_b) - 1;
	stop_at = next_idx - chonk_size;
	while (stack_size(*stack_b) > 0)
	{
		curr_idx = (*stack_b)->final_idx;
		while (curr_idx != next_idx && (*stack_b)->next->final_idx != stop_at)
		{
			rotate(stack_a, stack_b, 'b');
			curr_idx = (*stack_b)->final_idx;
		}
		while (curr_idx != next_idx)
		{
			reverse_rotate(stack_a, stack_b, 'b');
			curr_idx = (*stack_b)->final_idx;
		}
		push(stack_a, stack_b, 'a');
		next_idx--;
		if (next_idx == stop_at)
			stop_at -= chonk_size;
	}
}
