/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:17:56 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/30 16:11:55 by hsarhan          ###   ########.fr       */
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


static void	parse_error(char **args, int *nums, char *arg_string)
{
	if (args != NULL)
		free_split_array(args);
	if (nums != NULL)
		free(nums);
	if (arg_string != NULL)
		free(arg_string);
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}


static void	check_for_dups(char **args, int num_args, char *arg_string)
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
				parse_error(args, nums, arg_string);
			j++;
		}
		i++;
	}
	free(nums);
	free_split_array(args);
}

void	check_args(char *arg_string)
{
	char	**args;
	int		i;
	long	val;

	args = ft_split(arg_string, ' ');
	if (args == NULL)
	{
		free(arg_string);
		exit(EXIT_SUCCESS);
	}
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
			parse_error(args, NULL, arg_string);
		i++;
	}
	check_for_dups(args, i, arg_string);
}
