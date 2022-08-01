/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 12:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/31 13:50:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Join an argument from argv with another one while adding a space in the
// middle
char	*join_arg(const char *str1, const char *str2)
{
	char	*arg_with_space;
	char	*joined_args;

	arg_with_space = ft_strjoin(str1, " ");
	if (arg_with_space == NULL)
		return (NULL);
	joined_args = ft_strjoin(arg_with_space, str2);
	free(arg_with_space);
	if (joined_args == NULL)
		return (NULL);
	return (joined_args);
}

// Join all the args from argv together with a space in the middle
char	*arg_joiner(char **argv)
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
		if (ft_strlen(argv[i]) == 0)
		{
			free(joined_args);
			parse_error(NULL, NULL, NULL);
		}
		temp = joined_args;
		joined_args = join_arg(temp, argv[i]);
		free(temp);
		if (joined_args == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	return (joined_args);
}

// Fills stack a with parsed numbers from the command line
void	fill_stack(t_stack **stack, char **argv)
{
	char	*arg_string;
	int		*nums;
	int		num_args;
	int		i;
	t_stack	*stack_el;

	arg_string = arg_joiner(argv);
	nums = parse_args(arg_string, &num_args);
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
