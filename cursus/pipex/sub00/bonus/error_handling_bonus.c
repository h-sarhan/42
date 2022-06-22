/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:52:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 05:37:23 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Checks if a memory allocation fails and prints an error message
void	malloc_check(void *mem)
{
	if (mem == NULL && errno == ENOMEM)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

// Checks if a command is accessible and prints an error message if it is not
int	command_check(char **cmd_args, char *arg_list, int fd)
{
	char	**args;
	char	*cmd_name;
	int		i;

	if (cmd_args[0] == NULL)
	{
		args = ft_split(arg_list, ' ');
		malloc_check(args);
		cmd_name = ft_strdup(args[0]);
		malloc_check(cmd_name);
		free_split_array(args);
		if (fd != -1)
			print_error_string("command not found", cmd_name);
		ft_free(cmd_name);
		i = 0;
		while (cmd_args[++i] != NULL)
			ft_free(cmd_args[i]);
		return (0);
	}
	return (1);
}

// Wrapper around pipe() that handles errors
void	ft_pipe(int *pipe_fds)
{
	int	pipe_ret;

	pipe_ret = pipe(pipe_fds);
	if (pipe_ret == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

// Wrapper arounf fork that handles errors
int	ft_fork(int command_valid)
{
	int	pid;

	if (command_valid)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
		return (pid);
	}
	return (-1);
}

// Helper function that prints error messages
void	print_error_string(char *error_str, char *file_name)
{
	char	*str;

	str = ft_strjoin("pipex: ", file_name);
	str = ft_strjoinfree(str, ": ", 1);
	str = ft_strjoinfree(str, error_str, 1);
	ft_putendl_fd(str, 2);
	ft_free(str);
}
