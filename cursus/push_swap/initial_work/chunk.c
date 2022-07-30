/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 18:40:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	push_chunk_el(t_stack **stack_a, t_stack **stack_b, int pivot,
	bool *rot_b)
{
	if ((*stack_a)->final_idx > pivot)
	{
		if (*rot_b == true)
		{
			*rot_b = false;
			ft_printf("rb\n");
		}
		push(stack_a, stack_b, 'b');
	}
	else
	{
		if (*rot_b == true)
			ft_printf("rb\n");
		push(stack_a, stack_b, 'b');
		rotate(stack_a, stack_b, 'b', 1);
		*rot_b = true;
	}
}

void	chunk(t_stack **a, t_stack **b, int chunk_size)
{
	int		chunk_idx;
	bool	rot_b;

	chunk_idx = 0;
	rot_b = false;
	while (stack_size(*a) > 0)
	{
		while (stack_size(*a) > 0
			&& (*a)->final_idx >= chunk_idx * chunk_size
			&& (*a)->final_idx < (chunk_idx + 1) * chunk_size)
		{
			push_chunk_el(a, b, (chunk_idx + 0.5) * chunk_size, &rot_b);
			if (stack_size(*b) == (chunk_idx + 1) * chunk_size)
				chunk_idx++;
		}
		if (rot_b == true)
		{
			rotate(a, b, 'a', 1);
			ft_printf("rr\n");
			rot_b = false;
		}
		else
			rotate(a, b, 'a', false);
	}
}
