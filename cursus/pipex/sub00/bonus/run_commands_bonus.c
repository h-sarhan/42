/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:01:59 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 16:27:51 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Runs the command to the left of the pipe.
// If the infile file descriptor is invalid then it will be replaced
// with the "/dev/null" file descriptor which will return the EOF character
// when it is read from.
void	run_first_cmd(t_command *cmd, int *pipe_fds, int *fds, char **env)
{
	int	null_fd;

	null_fd = open_file("/dev/null", 0);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	if (fds[0] == -1)
		dup_fd(null_fd, STDIN);
	else
		dup_fd(cmd->in_fd, STDIN);
	dup_fd(cmd->out_fd, STDOUT);
	if (fds[0] != -1)
		execve(cmd->cmd_args[0], cmd->cmd_args, env);
	close_fd(pipe_fds[WRITE]);
	close_fd(fds[0]);
	close_fd(null_fd);
	exit(1);
}

void	run_middle_cmd(t_command *cmd, int *pipe_fds, int *fds, char **env)
{
	close_fd(fds[0]);
	close_fd(fds[1]);
	dup_fd(cmd->in_fd, STDIN);
	dup_fd(cmd->out_fd, STDOUT);
	execve(cmd->cmd_args[0], cmd->cmd_args, env);
	close_fd(pipe_fds[WRITE]);
	exit(1);
}

// Runs the command to the right of the pipe
void	run_last_cmd(t_command *cmd, int *pipe_fds, int *fds, char **env)
{
	close_fd(pipe_fds[WRITE]);
	close_fd(fds[0]);
	dup_fd(cmd->in_fd, STDIN);
	dup_fd(cmd->out_fd, STDOUT);
	if (fds[1] != -1)
		execve(cmd->cmd_args[0], cmd->cmd_args, env);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	exit(1);
}
