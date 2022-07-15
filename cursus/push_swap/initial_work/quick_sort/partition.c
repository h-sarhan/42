/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:40:29 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/15 18:01:42 by hsarhan          ###   ########.fr       */
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

void	partition_start(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*partition;

	partition = find_median(*stack_a);
	ft_printf("BEFORE PARTITIONING\n");
	int i = 0;
	int initial_size = stack_size(*stack_a);
	while (i < initial_size / 2)
	{
		push(stack_a, stack_b, 'b');
		i++;
	}
}