/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:52:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/28 17:07:30 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	forward_distance_to(t_stack **stack, int chunk_idx, int chunk_size)
{
	int	num_rots;
	int	i;

	// ft_printf("checking forward rotations\n");
	num_rots = 0;
	while (!((*stack)->final_idx >= chunk_idx * chunk_size 
		&& (*stack)->final_idx < (chunk_idx + 1) * chunk_size))
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

int	reverse_distance_to(t_stack **stack, int chunk_idx, int chunk_size)
{
	int	num_rots;
	int	i;

	num_rots = 0;
	// ft_printf("checking backward rotations\n");
	while (!((*stack)->final_idx >= chunk_idx * chunk_size 
		&& (*stack)->final_idx < (chunk_idx + 1) * chunk_size))
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



// USE THIS EXAMPLE
// 17 0 20 28 11 21 41 12 6 1 46 18 2 43 45 50 29 4 32 23
void	chunk(t_stack **stack_a, t_stack **stack_b, int chunk_size)
{
	int	chunk_idx;
	int	rev;
	int	rotated_b;
	// float	ratio;
	rev = 0;
	chunk_idx = 0;
	rotated_b = 0;
	// ratio = 0.4;
	while (stack_size(*stack_a) > 0)
	{
		while (stack_size(*stack_a) > 0 && (*stack_a)->final_idx >= chunk_idx * chunk_size
			&& (*stack_a)->final_idx < (chunk_idx + 1) * chunk_size)
		{
			if ((*stack_a)->final_idx > (chunk_idx + 0.5) * chunk_size)
			{
				if (rotated_b == 1)
				{
					rotated_b = 0;
					ft_printf("rb\n");
				}
				push(stack_a, stack_b, 'b');
			}
			else
			{
				if (rotated_b == 1)
				{
					ft_printf("rb\n");
				}
				push(stack_a, stack_b, 'b');
				rotate(stack_a, stack_b, 'b', 1);
				rotated_b = 1;
			}
			if (stack_size(*stack_b) == (chunk_idx + 1) * chunk_size)
				chunk_idx++;
		}
		if (rotated_b == 1)
		{
			rotate(stack_a, stack_b, 'a', 1);
			ft_printf("rr\n");
			rotated_b = 0;
		}
		else
		{
			rotate(stack_a, stack_b, 'a', 0);
		}
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


int	forward_distance_to_idx(t_stack **stack, int desired_idx)
{
	int	num_rots;
	int	i;

	// ft_printf("checking forward rotations\n");
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
	// ft_printf("forward rotations == %d\n", num_rots);
	return (num_rots);
}

int	reverse_distance_to_idx(t_stack **stack, int desired_idx)
{
	int	num_rots;
	int	i;

	num_rots = 0;
	// ft_printf("checking backward rotations\n");
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
	// ft_printf("backward rotations == %d\n", num_rots);
	return (num_rots);
}

// ! THIS CAN BE OPTIMIZED BY CHECKING IF THE SECOND LAREGEST ITEM IS CLOSER THAN THE LARGEST ITEM
// ! IF IT IS WE CAN PUSH THE SECOND LARGEST ITEM THEN SWAP A
void	sort_after_chunking(t_stack **stack_a, t_stack **stack_b, int chunk_size)
{
	int	next_idx;
	int	curr_idx;
	int	stop_at;
	int	rev;
	int	distance_to_alt_idx;
	// printf("SORTING\n");
	next_idx = stack_size(*stack_b) - 1;
	stop_at = next_idx - chunk_size;
	while (stack_size(*stack_b) > 0)
	{
		curr_idx = (*stack_b)->final_idx;
		if (which_direction(stack_b, next_idx))
			rev = 1;
		else
			rev = 0;
		if (next_idx > 1)
		{
			if (forward_distance_to_idx(stack_b, next_idx - 1))
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
		if (next_idx == stop_at)
			stop_at -= chunk_size;
	}
}
