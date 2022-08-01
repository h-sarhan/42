/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:09:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 10:46:31 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Find the stack element holding the smallest number and return it
t_stack	*find_min(t_stack *stack)
{
	int		min;
	t_stack	*min_stack;

	min = INT_MAX;
	min_stack = stack;
	while (stack != NULL)
	{
		if (stack->num < min)
		{
			min = stack->num;
			min_stack = stack;
		}
		stack = stack->next;
	}
	return (min_stack);
}

// Checks if the stack is sorted
bool	is_sorted_asc(t_stack *stack)
{
	if (stack_size(stack) < 2)
		return (true);
	while (stack->next != NULL)
	{
		if (stack->num > stack->next->num)
			return (false);
		stack = stack->next;
	}
	return (true);
}

// Like find_min but only looks at stack elements without a final_idx parameter
// Used in `get_final_positions`
static t_stack	*find_min2(t_stack *stack)
{
	int		min;
	t_stack	*min_stack;

	min = INT_MAX;
	min_stack = stack;
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

// Fills the final_idx paramter of each stack element
void	get_final_positions(t_stack *stack)
{
	t_stack	*min;
	int		idx;

	idx = 0;
	while (idx < stack_size(stack))
	{
		min = find_min2(stack);
		min->final_idx = idx;
		idx++;
	}
}

// Frees an array created by ft_split()
void	free_split_array(char **split_array)
{
	int	i;

	i = 0;
	while (split_array[i] != NULL)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}
