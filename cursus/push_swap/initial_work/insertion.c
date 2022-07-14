/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:43:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 16:14:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void insertion_sort(t_stack *stack_a, t_stack *stack_b)
{
	while (stack_size(stack_a) > 0)
		push(&stack_a, &stack_b, 'b'); 
	// AFTER THIS STACK B WILL BE STACK A IN REVERSE
	
	// WHILE STACK A IS NOT KIND OF SORTED AND STACK A SIZE != INITIAL SIZE
	// 		PUSH INTO STACK A UNTIL STACK A IS NOT KIND OF SORTED ANYMORE
	
	// 		RRA OR RA AND SA UNTIL STACK A IS KIND OF SORTED
	
	// IF STACK A IS KIND OF SORTED MAKE IT PROPER SORTED
}