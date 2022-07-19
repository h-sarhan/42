/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:09:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/19 22:07:49 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*find_min(t_stack *stack)
{
	int		min;
	t_stack	*min_stack;

	min = INT_MAX;
	while (stack != NULL)
	{
		if (stack->num < min && stack->final_idx == -1)
		{
			min = stack->num;
			min_stack = stack;
		}
		stack = stack->next;
	}
	return (min_stack);
}

int	is_sorted_desc(t_stack *stack)
{
	if (stack_size(stack) < 2)
		return (1);
	while (stack->next != NULL)
	{
		if (stack->num < stack->next->num)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	is_sorted_asc(t_stack *stack)
{
	if (stack_size(stack) < 2)
		return (1);
	while (stack->next != NULL)
	{
		if (stack->num > stack->next->num)
			return (0);
		stack = stack->next;
	}
	return (1);
}

t_stack	*find_max(t_stack *list)
{
	t_stack	*max;

	// list = list;
	max = list;
	while (list != NULL)
	{
		if (list->num > max->num)
			max = list;
		list = list->next;
	}
	return (max);
}

void	move_to_bottom(t_stack *min)
{
	t_stack	*stack;

	stack = min;
	while (min->next != NULL)
	{
		reverse_rotate(&stack, NULL, 'a', 0);
	}
}

void	print_stacks_side_by_side(t_stack *stack_a, t_stack *stack_b)
{
	ft_printf(" ===========\n");
	ft_printf("  A      B\n");
	while (stack_a != NULL && stack_b != NULL)
	{
		ft_printf(" [%d]    [%d]\n", stack_a->num, stack_b->num);
		ft_printf("  ↓      ↓\n");
		stack_a = stack_a->next;
		stack_b = stack_b->next;
	}
	if (stack_a == NULL && stack_b == NULL)
	{
		ft_printf(" NULL   NULL\n");
		ft_printf(" ===========\n");
		return ;
	}
	while (stack_a != NULL)
	{
		ft_printf(" [%d]       \n", stack_a->num);
		ft_printf("  ↓        \n");
		stack_a = stack_a->next;		
	}
	if (stack_a == NULL)
		ft_printf(" NULL     \n");
	while (stack_b != NULL)
	{
		ft_printf("        [%d]\n", stack_b->num);
		ft_printf("         ↓ \n");
		stack_b = stack_b->next;		
	}
	ft_printf("        NULL\n");
}