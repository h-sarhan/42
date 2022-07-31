/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 12:36:25 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 15:04:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static bool	do_move(char *move, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp(move, "sa\n", ft_strlen(move)) == 0)
		swap(stack_a, stack_b, 'a', true);
	else if (ft_strncmp(move, "sb\n", ft_strlen(move)) == 0)
		swap(stack_a, stack_b, 'b', true);
	else if (ft_strncmp(move, "ss\n", ft_strlen(move)) == 0)
		swap(stack_a, stack_b, 'c', true);
	else if (ft_strncmp(move, "pa\n", ft_strlen(move)) == 0)
		push(stack_a, stack_b, 'a', true);
	else if (ft_strncmp(move, "pb\n", ft_strlen(move)) == 0)
		push(stack_a, stack_b, 'b', true);
	else if (ft_strncmp(move, "ra\n", ft_strlen(move)) == 0)
		rotate(stack_a, stack_b, 'a', true);
	else if (ft_strncmp(move, "rb\n", ft_strlen(move)) == 0)
		rotate(stack_a, stack_b, 'b', true);
	else if (ft_strncmp(move, "rr\n", ft_strlen(move)) == 0)
		rotate(stack_a, stack_b, 'c', true);
	else if (ft_strncmp(move, "rra\n", ft_strlen(move)) == 0)
		reverse_rotate(stack_a, stack_b, 'a', true);
	else if (ft_strncmp(move, "rrb\n", ft_strlen(move)) == 0)
		reverse_rotate(stack_a, stack_b, 'b', true);
	else if (ft_strncmp(move, "rrr\n", ft_strlen(move)) == 0)
		reverse_rotate(stack_a, stack_b, 'c', true);
	else
		return (false);
	return (true);
}

static void	exit_checker(bool succ, bool sorted)
{
	if (!succ)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (sorted)
	{
		ft_printf("OK\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_printf("KO\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*stacks[2];
	char	*move;
	bool	succ;
	bool	sorted;

	stacks[0] = NULL;
	stacks[1] = NULL;
	sorted = false;
	succ = true;
	if (argc == 1)
		return (EXIT_SUCCESS);
	fill_stack(&stacks[0], argv);
	move = get_next_line(STDIN_FILENO);
	while (move != NULL)
	{
		if (!do_move(move, &stacks[0], &stacks[1]))
			succ = false;
		free(move);
		move = get_next_line(STDIN_FILENO);
	}
	if (is_sorted_asc(stacks[0]) && stack_size(stacks[1]) == 0)
		sorted = true;
	stack_clear(&stacks[0]);
	stack_clear(&stacks[1]);
	exit_checker(succ, sorted);
}
