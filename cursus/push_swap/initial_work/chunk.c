/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 17:33:36 by hsarhan          ###   ########.fr       */
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

int	which_direction(t_stack **stack, int desired_idx)
{
	int	num_forward_rots;
	int	num_backward_rots;
	int	i;

	num_forward_rots = 0;
	while ((*stack)->final_idx != desired_idx)
	{
		rotate(stack, NULL, 'a', 1);
		num_forward_rots++;
	}
	i = 0;
	while (i < num_forward_rots)
	{
		reverse_rotate(stack, NULL, 'a', 1);
		i++;
	}
	num_backward_rots = 0;
	while ((*stack)->final_idx != desired_idx)
	{
		reverse_rotate(stack, NULL, 'a', 1);
		num_backward_rots++;
	}
	i = 0;
	while (i < num_backward_rots)
	{
		rotate(stack, NULL, 'a', 1);
		i++;
	}
	return (num_backward_rots < num_forward_rots);
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

void	sort_after_chunking(t_stack **stack_a, t_stack **stack_b)
{
	int	next_idx;
	int	curr_idx;
	int	rev;
	int	distance_to_alt_idx;

	next_idx = stack_size(*stack_b) - 1;
	while (stack_size(*stack_b) > 0)
	{
		curr_idx = (*stack_b)->final_idx;
		if (which_direction(stack_b, next_idx))
			rev = 1;
		else
			rev = 0;
		if (next_idx > 1)
		{
			if (forward_dist(stack_b, next_idx - 1) < reverse_dist(stack_b, next_idx - 1))
				distance_to_alt_idx = forward_dist(stack_b, next_idx - 1);
			else
				distance_to_alt_idx = reverse_dist(stack_b, next_idx - 1);
			if (distance_to_alt_idx < reverse_dist(stack_b, next_idx)
				&& distance_to_alt_idx < forward_dist(stack_b, next_idx))
			{
				if (which_direction(stack_b, next_idx - 1))
					rev = 1;
				else
					rev = 0;
				while (curr_idx != next_idx - 1)
				{
					if (rev)
						reverse_rotate(stack_a, stack_b, 'b', 0);
					else
						rotate(stack_a, stack_b, 'b', 0);
					curr_idx = (*stack_b)->final_idx;
				}
				push(stack_a, stack_b, 'a');
				if (which_direction(stack_b, next_idx))
					rev = 1;
				else
					rev = 0;
				curr_idx = (*stack_b)->final_idx;
				while (curr_idx != next_idx)
				{
					if (rev)
						reverse_rotate(stack_a, stack_b, 'b', 0);
					else
						rotate(stack_a, stack_b, 'b', 0);
					curr_idx = (*stack_b)->final_idx;
				}
				push(stack_a, stack_b, 'a');
				swap(stack_a, stack_b, 'a');
				next_idx -= 2;
				continue ;
			}
		}
		while (curr_idx != next_idx)
		{
			if (rev)
				reverse_rotate(stack_a, stack_b, 'b', 0);
			else
				rotate(stack_a, stack_b, 'b', 0);
			curr_idx = (*stack_b)->final_idx;
		}
		push(stack_a, stack_b, 'a');
		next_idx--;
	}
}
