/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chonk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/20 07:00:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	forward_distance_to(t_stack **stack, int chonk_idx, int chonk_size)
{
	int	num_rots;
	int	i;

	// ft_printf("checking forward rotations\n");
	num_rots = 0;
	while (!((*stack)->final_idx >= chonk_idx * chonk_size 
		&& (*stack)->final_idx < (chonk_idx + 1) * chonk_size))
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
	// ft_printf("forward rotations == %d\n", num_rots);
	return (num_rots);
}

int	reverse_distance_to(t_stack **stack, int chonk_idx, int chonk_size)
{
	int	num_rots;
	int	i;

	num_rots = 0;
	// ft_printf("checking backward rotations\n");
	while (!((*stack)->final_idx >= chonk_idx * chonk_size 
		&& (*stack)->final_idx < (chonk_idx + 1) * chonk_size))
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
	// ft_printf("backward rotations == %d\n", num_rots);
	return (num_rots);
}


// int	mid_chonk()
// {
// 	stack_size(*stack_a) > 0 && (*stack_a)->final_idx >= chonk_idx * chonk_size
// 			&& (*stack_a)->final_idx < (chonk_idx + 1) * chonk_size
// }

// USE THIS EXAMPLE
// 17 0 20 28 11 21 41 12 6 1 46 18 2 43 45 50 29 4 32 23
void	chonk(t_stack **stack_a, t_stack **stack_b, int chonk_size)
{
	int	chonk_idx;
	int	rev;
	int push_count;
	// int	rotated_a;

	push_count = 0;
	rev = 0;
	chonk_idx = 0;
	// if (forward_distance_to(stack_a, chonk_idx, chonk_size) > 
	// 	reverse_distance_to(stack_a, chonk_idx, chonk_size))
	// 	rev = 1;
	while (stack_size(*stack_a) > 0)
	{
		while (stack_size(*stack_a) > 0 && (*stack_a)->final_idx >= chonk_idx * chonk_size
			&& (*stack_a)->final_idx < (chonk_idx + 1) * chonk_size)
		{
			// if (push_count % 2 == 0)
			// {
			// 	rotate(stack_a, stack_b, 'b', 0);
			// }
			// if ((*stack_a)->final_idx % 2 == 0)
			// 	rotate(stack_a, stack_b, 'a');
			push(stack_a, stack_b, 'b');
			push_count++;
			if (stack_size(*stack_b) == (chonk_idx + 1) * chonk_size)
				chonk_idx++;
			// print_stacks_side_by_side(*stack_a, *stack_b);
			// if (stack_size(*stack_a) > 0 && forward_distance_to(stack_a, chonk_idx, chonk_size) > 
			// 	reverse_distance_to(stack_a, chonk_idx, chonk_size))
			// 	rev = 1;
			// else
			// 	rev = 0;
			// reverse_rotate();
		}
		rotate(stack_a, stack_b, 'a', 0);
		// if (rev)
		// 	reverse_rotate(stack_a, stack_b, 'a', 0);
		// else
		// {
			// rotate(stack_a, stack_b, 'a', 0);
		// }
		// print_stacks_side_by_side(*stack_a, *stack_b);
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


void	sort_after_chonking(t_stack **stack_a, t_stack **stack_b, int chonk_size)
{
	int	next_idx;
	int	curr_idx;
	int	stop_at;
	int	rev;
	
	next_idx = stack_size(*stack_b) - 1;
	stop_at = next_idx - chonk_size;
	while (stack_size(*stack_b) > 0)
	{
		curr_idx = (*stack_b)->final_idx;
		if (which_direction(stack_b, next_idx))
			rev = 1;
		else
			rev = 0;
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
		if (next_idx == stop_at)
			stop_at -= chonk_size;
	}
}
