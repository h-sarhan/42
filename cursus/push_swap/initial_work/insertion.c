/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:43:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 19:28:14 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void insertion_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	initial_size = stack_size(stack_a);
	while (stack_size(stack_a) > 0)
		push(&stack_a, &stack_b, 'b'); 
	// AFTER THIS STACK B WILL BE STACK A IN REVERSE
	// WHILE STACK A IS NOT KIND OF SORTED AND STACK A SIZE != INITIAL SIZE
	while (stack_size(stack_a) < initial_size)
	{
		// PUSH INTO STACK A UNTIL STACK A IS NOT KIND OF SORTED ANYMORE
		while (kind_of_sorted_asc(stack_a) && stack_size(stack_a) < initial_size)
		{
			push(&stack_a, &stack_b, 'a');
		}
		// if (stack_size(stack_a) == initial_size)
		// 	break ;
		// RRA OR RA AND SA UNTIL STACK A IS KIND OF SORTED
		while (!kind_of_sorted_asc(stack_a))
		{
			stack_print(stack_a);
			
			swap(&stack_a, &stack_b, 'a');
			rotate(&stack_a, &stack_b, 'a');
		}
	}
	// IF STACK A IS NOT PROPER SORTED MAKE IT PROPER SORTED
	while (!is_sorted_asc(stack_a))
	{
		rotate(&stack_a, &stack_b, 'a');
	}
}