/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:17:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/11/17 21:23:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Checks if an argument is numeric
static bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		if ((str[i] == '-' || str[i] == '+') && i != 0)
			return (false);
		if ((str[i] == '-' || str[i] == '+') && ft_strlen(str) == 1)
			return (false);
		i++;
	}
	return (true);
}

// Exits the program, frees what is necessary, and prints an error message, not
// in that order.
void	parse_error(char **args, int *nums, char *arg_string)
{
	if (args != NULL)
		free_split_array(args);
	if (nums != NULL)
		free(nums);
	if (arg_string != NULL)
		free(arg_string);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

// Checks the arguments for duplicates
static int	*check_for_dups(char **args, int num_args)
{
	int	*nums;
	int	i;
	int	j;

	i = 0;
	nums = ft_calloc(num_args, sizeof(int));
	if (nums == NULL)
	{
		free_split_array(args);
		exit(EXIT_FAILURE);
	}
	while (i < num_args)
	{
		nums[i] = ft_atol(args[i]);
		j = 0;
		while (j < i)
		{
			if (nums[j] == nums[i])
				parse_error(args, nums, NULL);
			j++;
		}
		i++;
	}
	free_split_array(args);
	return (nums);
}

// Parses the argument strings passed to push_swap
int	*parse_args(char *arg_string, int *num_args)
{
	char	**args;
	int		i;
	long	val;

	args = ft_split(arg_string, ' ');
	free(arg_string);
	if (args == NULL)
		exit(EXIT_FAILURE);
	if (args[0] == NULL)
	{
		free_split_array(args);
		exit(EXIT_SUCCESS);
	}
	i = 0;
	while (args[i] != NULL)
	{
		val = ft_atol(args[i]);
		if (!is_numeric(args[i]) || val > INT_MAX || val < INT_MIN)
			parse_error(args, NULL, NULL);
		i++;
	}
	*num_args = i;
	return (check_for_dups(args, i));
}
