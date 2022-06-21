/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_calls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:46:59 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/21 10:02:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(void *mem)
{
	if (mem != NULL)
		free(mem);
}

void	dup_fd(int fd_1, int fd_2)
{
	int	dup_ret;

	if (fd_1 != -1)
	{
		dup_ret = dup2(fd_1, fd_2);
		if (dup_ret == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_fd(int fd)
{
	int	close_ret;

	if (fd != -1)
	{
		close_ret = close(fd);
		if (close_ret == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
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

void	run_command(int *pipe_fds, int *fds, char **cmd_args, char **env)
{
	int	null_fd;

	null_fd = open_file("/dev/null", 0);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	if (fds[0] == -1)
		dup_fd(null_fd, STDIN);
	else
		dup_fd(fds[0], STDIN);
	dup_fd(pipe_fds[WRITE], STDOUT);
	if (fds[0] != -1)
		execve(cmd_args[0], cmd_args, env);
	close_fd(pipe_fds[WRITE]);
	close_fd(fds[0]);
	close_fd(null_fd);
	free_split_array(cmd_args);
	exit(1);
}
