/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:52:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/18 08:05:15 by hsarhan          ###   ########.fr       */
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

void	fd_check(int fd, char *file_name)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(file_name, 2);
	}
}

void command_check(char *cmd_path, char *cmd_args)
{
	char	**args;
	char	*cmd_name;
	
	if (cmd_path == NULL && errno == ENOENT)
	{
		args = ft_split(cmd_args, ' ');
		malloc_check(args);
		cmd_name = ft_strdup(args[0]);
		malloc_check(cmd_name);
		free_split_array(args);
		// TODO: Write "command not found" message instead
		perror(cmd_name);
		ft_free(cmd_name);
	}
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
