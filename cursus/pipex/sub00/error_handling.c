/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:52:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/18 13:47:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	malloc_check(void *mem)
{
	if (mem == NULL && errno == ENOMEM)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

int	fd_check(int fd, char *file_name)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(file_name, 2);
		return (0);
	}
	return (1);
}

int command_check(char **cmd_args, char *arg_list, int *exit_code, int fd)
{
	char	**args;
	char	*cmd_name;
	int		i;

	if (cmd_args[0] == NULL && errno == ENOENT)
	{
		args = ft_split(arg_list, ' ');
		malloc_check(args);
		cmd_name = ft_strdup(args[0]);
		malloc_check(cmd_name);
		free_split_array(args);
		if (fd != -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(cmd_name, 2);
		}
		ft_free(cmd_name);
		if (exit_code != NULL)
			*exit_code = 127;
		i = 0;
		while (cmd_args[++i] != NULL)
			ft_free(cmd_args[i]);
		return (0);
	}
	return (1);
}

void	pipe_check(int pipe_ret)
{
	if (pipe_ret == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

void	fork_check(int pid)
{
	if (pid == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
