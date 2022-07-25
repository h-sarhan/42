/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:57:38 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/25 16:28:28 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"


// TODO: Create a struct and sort it to find the shortest path
// https://www.geeksforgeeks.org/shortest-path-to-traverse-all-the-elements-of-a-circular-array-in-increasing-order/

struct	s_path
{
	int		*positions;
	int		*indices;
	char	*direction;
	int		size;
};

typedef struct s_path	t_path;


void	swap_els(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	find_min_val(int *arr, int size)
{
	int	i;
	int	min;

	i = 0;
	min = 0;
	while (i < size)
	{
		if (arr[i] < arr[min])
			min = i;
		i++;
	}
	return (min);
}


void	selection_sort(t_path *path)
{
	int	i;
	int	min;

	i = 0;
	while (i < path->size)
	{
		min = find_min_val(&path->positions[i], path->size - i) + i;
		swap_els(&path->positions[i], &path->positions[min]);
		swap_els(&path->indices[i], &path->indices[min]);
		i++;
	}
}

void	create_path(t_path *path)
{
	int	i = 1;
	while (i < path->size)
	{
		// TODO: Write an abs function
		if (abs(path->indices[i] - path->indices[i - 1]) 
		> path->size - abs(path->indices[i] - path->indices[i - 1]))
		{
			path->direction[i] = 'r';
			// printf("R\n");
		}
		else
		{
			path->direction[i] = 'f';
			// printf("F\n");
		}
		i++;
	}
}

char	*shortest_path(t_stack *stack)
{
	// char	*path;
	t_path	path;
	
	path.size = stack_size(stack);
	// TODO: PROTECT THESE!!
	path.direction = ft_calloc(path.size + 1, sizeof(char));
	path.positions = ft_calloc(path.size, sizeof(int *));
	path.indices = ft_calloc(path.size, sizeof(int *));
	int i = 0;
	while (stack != NULL)
	{
		path.indices[i] = i;
		path.positions[i] = stack->final_idx;
		stack = stack->next;
		i++;
	}
	selection_sort(&path);
	// for (int i = 0; i < path.size; i++)
	// 	ft_printf("value %d, idx %d\n", path.positions[i], path.indices[i]);
	create_path(&path);
	return path.direction;
}
