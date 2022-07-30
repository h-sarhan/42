/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:40:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 18:40:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	dist_to(t_stack **stack, int desired_idx, bool *rev)
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

void	push_element(t_stack **stacks, int curr_idx, int desired_idx, bool rev)
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
