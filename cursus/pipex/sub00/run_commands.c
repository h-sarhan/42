/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:01:59 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:43:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Runs the command to the left of the pipe.
// If the infile file descriptor is invalid then it will be replaced
// with the "/dev/null" file descriptor which will return the EOF character
// when it is read from.
void	run_first_cmd(t_cmd *cmd, int *pipe_fds, int *fds, t_list *cmds)
{
	int	null_fd;

	null_fd = open_file("/dev/null", 0);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	if (fds[0] == -1)
	{
		dup_fd(null_fd, STDIN);
		close_fd(cmd->in_fd);
	}
	else
	{
		dup_fd(cmd->in_fd, STDIN);
		close_fd(null_fd);
	}
	dup_fd(cmd->out_fd, STDOUT);
	if (fds[0] != -1)
		execve(cmd->cmd_args[0], cmd->cmd_args, environ);
	ft_lstclear(&cmds, free_cmd);
	close_fd(pipe_fds[WRITE]);
	close_fd(fds[0]);
	close_fd(null_fd);
	close_fd(STDOUT);
	close_fd(STDIN);
	exit(1);
}

// Runs a command in the middle
void	run_middle_cmd(t_cmd *cmd, int *pipe_fds, int *fds, t_list *cmds)
{
	close_fd(fds[0]);
	close_fd(fds[1]);
	close_fd(pipe_fds[READ]);
	dup_fd(cmd->in_fd, STDIN);
	dup_fd(cmd->out_fd, STDOUT);
	execve(cmd->cmd_args[0], cmd->cmd_args, environ);
	ft_lstclear(&cmds, free_cmd);
	close_fd(pipe_fds[WRITE]);
	exit(1);
}

// Runs the last command
void	run_last_cmd(t_cmd *cmd, int *pipe_fds, int *fds, t_list *cmds)
{
	close_fd(fds[0]);
	dup_fd(cmd->in_fd, STDIN);
	dup_fd(cmd->out_fd, STDOUT);
	if (fds[1] != -1)
		execve(cmd->cmd_args[0], cmd->cmd_args, environ);
	ft_lstclear(&cmds, free_cmd);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	close_fd(STDIN);
	exit(1);
}
