/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chonk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/20 08:16:41 by hsarhan          ###   ########.fr       */
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
	int initial_size = stack_size(*stack_a);
	while (stack_size(*stack_a) > initial_size / 2)
	{
		while ((*stack_a)->final_idx % 2 == 0 && (*stack_a)->final_idx >= chonk_idx * chonk_size
			&& (*stack_a)->final_idx <= (chonk_idx + 1) * chonk_size)
		{
			push(stack_a, stack_b, 'b');
			push_count++;
			printf("IN HERE\n");
			if (stack_size(*stack_b) == (chonk_idx + 1) * chonk_size / 2 + 1)
				chonk_idx++;
		}
		// printf("THIS ONE\n");
		rotate(stack_a, stack_b, 'a', 0);
	}
	initial_size = stack_size(*stack_b);
	chonk_idx = 0;
	while (stack_size(*stack_a) > 0)
	{
		while (stack_size(*stack_a) > 0 && (*stack_a)->final_idx >= chonk_idx * chonk_size
			&& (*stack_a)->final_idx <= (chonk_idx + 1) * chonk_size)
		{
			if (stack_size(*stack_b) == (initial_size) + (chonk_idx + 1) * chonk_size / 2)
				chonk_idx++;
			push(stack_a, stack_b, 'b');
			push_count++;
			printf("IN HERE\n");
		}
		if ((*stack_a)->final_idx % 2 != 0)
		{
			ft_printf("chonk_idx is %d\n", chonk_idx);
			ft_printf("chonk_size is %d\n", chonk_size);
			ft_printf("Stack size is %d\n", stack_size(*stack_b));
			ft_printf("chonk_range is between %d and %d\n", chonk_idx * chonk_size, (chonk_idx + 1) * chonk_size);
			ft_printf("stack_size should reach %d\n", (initial_size + 1) + (chonk_idx + 1) * chonk_size / 2);
			ft_printf("stack_a el final idx is %d\n", (*stack_a)->final_idx);
		}
		print_stacks_side_by_side(*stack_a, *stack_b); //
		rotate(stack_a, stack_b, 'a', 0);
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
