/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:57:38 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/25 13:37:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

void	swap_els(int **a, int **b)
{
	int	temp[2];

	temp[0] = (*a)[0];
	temp[1] = (*a)[1];
	*a = *b;
	*b = temp;
}

int	**find_min_val(int **arr, int size)
{
	int	i;
	int	**min;

	i = 0;
	min = arr;
	while (i < size)
	{
		if (arr[i][0] < (*min)[0])
			min = &arr[i];
		i++;
	}
	return (min);
}

void	selection_sort(int **arr, int size)
{
	int	i;
	int	**min;

	i = 0;
	while (i < size)
	{
		min = find_min_val(&arr[i], size - i);
		printf("MIN IS %d\n", min[0][0]);
		// swap_els(&arr[i], min);
		i++;
	}
}


char	*shortest_path(t_stack *stack)
{
	int	**elements;
	char	*path;
	int	num_elements;
	
	num_elements = stack_size(stack);
	// TODO: PROTECT THIS!!
	path = ft_calloc(num_elements + 1, sizeof(char));
	elements = ft_calloc(num_elements, sizeof(int *));
	if (elements == NULL)
		return (NULL); // ! OR EXIT
	int i = 0;
	while (stack != NULL)
	{
		elements[i] = ft_calloc(2, sizeof(int));
		if (elements[i] == NULL)
			return (NULL); // ! OR EXIT
		elements[i][0] = stack->final_idx;
		elements[i][1] = i;
		stack = stack->next;
		i++;
	}
	if (path == NULL)
		return (NULL); // ! OR EXIT
		
	selection_sort(elements, num_elements);
	for (int i = 0; i < num_elements; i++)
		ft_printf("value %d, idx %d\n", elements[i][0], elements[i][1]);
}
