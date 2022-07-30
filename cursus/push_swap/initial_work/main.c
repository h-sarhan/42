/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 06:42:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 18:07:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*join_arg(const char *str1, const char *str2)
{
	char	*arg_with_space;
	char	*joined_args;

	arg_with_space = ft_strjoin(str1, " ");
	if (arg_with_space == NULL)
		return (NULL);
	joined_args = ft_strjoin(arg_with_space, str2);
	free(arg_with_space);
	if (joined_args == NULL)
	{
		free(arg_with_space);
		return (NULL);
	}
	return (joined_args);
}

static char	*arg_joiner(char **argv)
{
	char	*joined_args;
	char	*temp;
	int		i;

	i = 1;
	joined_args = ft_strdup("");
	if (joined_args == NULL)
		exit(EXIT_FAILURE);
	while (argv[i] != NULL)
	{
		temp = joined_args;
		joined_args = join_arg(temp, argv[i]);
		free(temp);
		if (joined_args == NULL)
		{
			free(temp);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (joined_args);
}

void	fill_stack(t_stack **stack, char **argv)
{
	char	*arg_string;
	int		*nums;
	int		num_args;
	int		i;
	t_stack	*stack_el;

	arg_string = arg_joiner(argv);
	nums = parse_args(arg_string, &num_args);
	free(arg_string);
	i = 0;
	while (i < num_args)
	{
		stack_el = stack_new(nums[i++]);
		if (stack_el == NULL)
		{
			stack_clear(stack);
			free(nums);
			exit(EXIT_FAILURE);
		}
		stack_add_bottom(stack, stack_el);
	}
	free(nums);
}

int	main(int argc, char **argv)
{
	t_stack	*stacks[2];
	// t_stack	*stack_a;
	// t_stack	*stacks[1];
	int		chunk_size;

	stacks[0] = NULL;
	stacks[1] = NULL;
	if (argc == 1)
		return (EXIT_SUCCESS);
	fill_stack(&stacks[0], argv);
	get_final_positions(stacks[0]);
	if (is_sorted_asc(stacks[0]))
	{
		stack_clear(&stacks[0]);
		return (0);
	}
	if (stack_size(stacks[0]) <= 5)
		sort_small(stacks[0], stacks[1]);
	else
	{
		chunk_size = 0.1075 * stack_size(stacks[0]) + 6.25;
		chunk(&stacks[0], &stacks[1], chunk_size);
		sort_after_chunking(&stacks[0], &stacks[1]);
	}
	stack_clear(&stacks[0]);
}
