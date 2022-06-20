/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:50:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 16:51:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoinfree(char *s1, char *s2, int f)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (f == 1)
		ft_free(s1);
	if (f == 2)
		ft_free(s2);
	if (f == 3)
	{
		ft_free(s1);
		ft_free(s2);
	}
	return (joined);
}

void	free_split_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

void	trim_args(char **args)
{
	int		i;
	char	*trimmed_arg;
	char	*quote;

	i = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '\'' || args[i][0] == '\"')
		{
			quote = malloc(2);
			quote[0] = args[i][0];
			quote[1] = '\0';
			trimmed_arg = ft_strtrim(args[i], quote);
			free(args[i]);
			free(quote);
			args[i] = trimmed_arg;
		}
		i++;
	}
}

void	wait_and_exit(int *pids, int out_fd, int cmd_2_valid)
{
	int	w_status;

	if (pids[0] != -1)
		waitpid(pids[0], &w_status, 0);
	if (pids[1] != -1)
		waitpid(pids[1], &w_status, 0);
	if (out_fd == -1)
		exit(1);
	if (!cmd_2_valid)
		exit(127);
	exit(WEXITSTATUS(w_status));
}

void	check_arg_count(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		exit(EXIT_FAILURE);
	}
}
