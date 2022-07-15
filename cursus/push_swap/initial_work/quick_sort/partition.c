/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:40:29 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 18:50:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	compare_ints(const void *a, const void *b)
{
	if (*(int *)a < *(int *)b)
		return (-1);
	if (*(int *)a > *(int *)b)
		return (1);
	return (0);
}

t_stack	*find_median(t_stack *stack)
{
	int	*els;
	int	i;
	int	median_num;
	t_stack *median;
	
	median = stack;
	// TODO: PROTECT THIS
	els = ft_calloc(stack_size(stack), sizeof(int));
	i = 0;
	while (stack != NULL)
	{
		els[i] = stack->num;
		stack = stack->next;
		i++;
	}
	// TODO: REPLACE THIS WITH MY OWN IMPLEMENTAION
	qsort(els, stack_size(median), sizeof(int), compare_ints);
	median_num = els[stack_size(median) / 2];
	while (median != NULL)
	{
		if (median->num == median_num)
			return (median);
		median = median->next;
	}
	return (median);
}

int	contains_smaller_than(t_stack *stack, int num)
{
	while (stack != NULL)
	{
		if (stack->num < num)
			return (1);
		stack = stack->next;
	}
	return (0);
}
int	contains_greater_than(t_stack *stack, int num)
{
	while (stack != NULL)
	{
		if (stack->num > num)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void	reposition_top(t_stack **stack, t_stack *desired_top)
{
	// TODO: 10000000% CAN BE OPTIMIZED
	while (*stack != desired_top)
		rotate(stack, NULL, 'a');
}

void	reposition_bottom(t_stack **stack, t_stack *desired_bottom)
{
	// TODO: 10000000% CAN BE OPTIMIZED
	while (stack_bottom(*stack) != desired_bottom)
		rotate(stack, NULL, 'a');
}

void	partition_start(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*partition;

	partition = find_median(*stack_a);
	// ft_printf("BEFORE PARTITIONING\n");
	int i = 0;
	int initial_size = stack_size(*stack_a);
	while (i < initial_size / 2)
	{
		push(stack_a, stack_b, 'b');
		i++;
	}
	// ft_printf("Partitioning on element %d\n", partition->num);
	
	// TODO: MAYBE ROTATION CAN BE OPTIMIZED
	// ? MOVE ELEMENTS IN STACK A GREATER THAN PARTITION INTO STACK B
	while (contains_greater_than(*stack_a, partition->num))
	{
		while ((*stack_a)->num <= partition->num)
			rotate(stack_a, stack_b, 'a');
		push(stack_a, stack_b, 'b');
	}
	// TODO: MAYBE ROTATION CAN BE OPTIMIZED
	// ? MOVE ELEMENTS IN STACK B SMALLER THAN PARTITION INTO STACK A
	while (contains_smaller_than(*stack_b, partition->num))
	{
		while ((*stack_b)->num >= partition->num)
			rotate(stack_a, stack_b, 'b');
		push(stack_a, stack_b, 'a');
	}
	// print_stacks_side_by_side(*stack_a, *stack_b);
	reposition_top(stack_a, partition);
	print_stacks_side_by_side(*stack_a, *stack_b);
}

void	partition_left(t_stack **stack_a, t_stack **stack_b)
{
	
}
