/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:52:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 14:35:26 by hsarhan          ###   ########.fr       */
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

int	open_file(char *file_path, int outfile)
{
	int		mode;
	int		fd;
	
	fd = 1;
	mode = R_OK;
	if (outfile == 1)
		mode = W_OK;
	if (outfile != 1 && access(file_path, mode) == -1)
		fd = -1;
	else if (outfile == 1)
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		print_error_string(strerror(errno), file_path);
		return (-1);
	}
	return (fd);
}

int command_check(char **cmd_args, char *arg_list, int fd)
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

void	print_error_string(char *error_str, char *file_name)
{
	char	*str;
	
	str = ft_strjoin("pipex: ", file_name);
	str = ft_strjoinfree(str, ": ", 1);
	str = ft_strjoinfree(str, error_str, 1);
	ft_putendl_fd(str, 2);
	ft_free(str);
}

void	fork_check(int pid)
{
	if (pid == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
