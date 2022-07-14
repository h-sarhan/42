/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:43:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/14 16:04:01 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void insertion_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*max;
	while (stack_size(stack_a) > 0)
		push(&stack_a, &stack_b, 'b'); 
}