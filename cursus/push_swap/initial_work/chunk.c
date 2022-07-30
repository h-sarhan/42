/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 18:06:11 by hsarhan          ###   ########.fr       */
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


int	forward_dist(t_stack **stack, int desired_idx)
{
	int	num_rots;
	int	i;

	num_rots = 0;
	while ((*stack)->final_idx != desired_idx)
	{
		rotate(stack, NULL, 'a', 1);
		num_rots++;
	}
	i = 0;
	while (i < num_rots)
	{
		reverse_rotate(stack, NULL, 'a', 1);
		i++;
	}
	return (num_rots);
}

int	reverse_dist(t_stack **stack, int desired_idx)
{
	int	num_rots;
	int	i;

	num_rots = 0;
	while ((*stack)->final_idx != desired_idx)
	{
		reverse_rotate(stack, NULL, 'a', 1);
		num_rots++;
	}
	i = 0;
	while (i < num_rots)
	{
		rotate(stack, NULL, 'a', 1);
		i++;
	}
	return (num_rots);
}

int	distance_to(t_stack **stack, int desired_idx, bool *rev)
{
	int	num_forward_rots;
	int	num_backward_rots;

	num_forward_rots = forward_dist(stack, desired_idx);
	num_backward_rots = reverse_dist(stack, desired_idx);
	if (num_forward_rots < num_backward_rots)
	{
		*rev = false;
		return (num_forward_rots);
	}
	else
	{
		*rev = true;
		return (num_backward_rots);
	}
}

void	fwd_push_element(t_stack **stack_a, t_stack **stack_b, int curr_idx,
	int desired_idx)
{
	while (curr_idx != desired_idx)
	{
		rotate(stack_a, stack_b, 'b', false);
		curr_idx = (*stack_b)->final_idx;
	}
}

void	rev_push_element(t_stack **stack_a, t_stack **stack_b, int curr_idx,
	int desired_idx)
{
	while (curr_idx != desired_idx)
	{
		reverse_rotate(stack_a, stack_b, 'b', false);
		curr_idx = (*stack_b)->final_idx;
	}
}

void	sort_after_chunking(t_stack **stack_a, t_stack **stack_b)
{
	int		next_idx;
	int		curr_idx;
	bool	rev[2];
	int		distance_to_alt_idx;
	int		distance_to_next_idx;

	next_idx = stack_size(*stack_b) - 1;
	while (stack_size(*stack_b) > 0)
	{
		curr_idx = (*stack_b)->final_idx;
		distance_to_next_idx = distance_to(stack_b, next_idx, &rev[0]);
		if (next_idx > 1)
		{
			distance_to_alt_idx = distance_to(stack_b, next_idx - 1, &rev[1]);
			if (distance_to_alt_idx < distance_to_next_idx)
			{
				if (rev[1])
					rev_push_element(stack_a, stack_b, curr_idx, next_idx - 1);
				else
					fwd_push_element(stack_a, stack_b, curr_idx, next_idx - 1);
				push(stack_a, stack_b, 'a');
				distance_to_next_idx = distance_to(stack_b, next_idx, &rev[0]);
				curr_idx = (*stack_b)->final_idx;
				if (rev[0])
					rev_push_element(stack_a, stack_b, curr_idx, next_idx);
				else
					fwd_push_element(stack_a, stack_b, curr_idx, next_idx);
				push(stack_a, stack_b, 'a');
				swap(stack_a, stack_b, 'a');
				next_idx -= 2;
				continue ;
			}
		}
		if (rev[0])
			rev_push_element(stack_a, stack_b, curr_idx, next_idx);
		else
			fwd_push_element(stack_a, stack_b, curr_idx, next_idx);
		push(stack_a, stack_b, 'a');
		next_idx--;
	}
}
