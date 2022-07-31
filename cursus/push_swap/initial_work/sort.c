/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:40:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 10:59:25 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Returns the number of forward rotations needed to reach a stack element
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

// Returns the number of reverse rotations needed to reach a stack element
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

// Returns the minimum distance to a stack element, either through forward
// or reverse rotations. Also sets the rev parameter to true if reverse
// rotating to the desired element is faster
static int	dist_to(t_stack **stack, int desired_idx, bool *rev)
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

// Rotates to a stack element in stack b and pushes it to stack a
static void	push_element(t_stack **stacks, int curr_idx,
	int desired_idx, bool rev)
{
	while (curr_idx != desired_idx)
	{
		if (rev)
			reverse_rotate(&stacks[0], &stacks[1], 'b', false);
		else
			rotate(&stacks[0], &stacks[1], 'b', false);
		curr_idx = stacks[1]->final_idx;
	}
	push(&stacks[0], &stacks[1], 'a');
}

// Main sorting algorithm
// After chunking, the elements in stack b will be relatively sorted, so
// the number of rotations needed to get to each element is lower.
// This algorithm will simply rotate to the biggest index, push it to stack A
// and decrement the index. One important optimization included is that if the
// second biggest index is closer than the biggest one then I rotate to it, push
// it, rotate to biggest, push that, then swap A.
void	sort_after_chunking(t_stack **stacks)
{
	int		next_idx;
	int		curr_idx;
	bool	rev[2];
	int		dist_to_next;

	next_idx = stack_size(stacks[1]) - 1;
	while (stack_size(stacks[1]) > 0)
	{
		curr_idx = (stacks[1])->final_idx;
		dist_to_next = dist_to(&stacks[1], next_idx, &rev[0]);
		if (next_idx > 1
			&& dist_to(&stacks[1], next_idx - 1, &rev[1]) < dist_to_next)
		{
			push_element(stacks, curr_idx, next_idx - 1, rev[1]);
			dist_to_next = dist_to(&stacks[1], next_idx, &rev[0]);
			curr_idx = stacks[1]->final_idx;
			push_element(stacks, curr_idx, next_idx, rev[0]);
			swap(&stacks[0], &stacks[1], 'a');
			next_idx -= 2;
			continue ;
		}
		push_element(stacks, curr_idx, next_idx, rev[0]);
		next_idx--;
	}
}
