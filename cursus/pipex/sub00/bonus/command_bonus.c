/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:27:28 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 11:17:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_command	*create_command(char *cmd_str, char **env)
{
	t_command	*cmd;
	int			status;

	cmd = ft_calloc(1, sizeof(t_command));
	malloc_check(cmd);
	cmd->cmd_args = get_args(cmd_str, env);
	cmd->pid = -1;
	cmd->valid = 0;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	cmd->w_status = &status;
	return (cmd);
}

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
	// FREE COMMANDS HERE
	// free_split_array(cmd_args[0]);
	// free_split_array(cmd_args[1]);
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
	// FREE COMMANDS HERE
	// free_split_array(cmd_args[1]);
	exit(1);
}

// Runs the command to the right of the pipe
// void	run_command2(int *pipe_fds, int *fds, char **cmd_args, char **env)
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
	// FREE COMMANDS HERE
	// free_split_array(cmd_args[1]);
	exit(1);
}

void	free_cmd(void *cmd)
{
	t_command *command;
	
	command = cmd;
	free_split_array(command->cmd_args);
	free(command);
}

void	wait_cmd(void *cmd)
{
	t_command	*command;

	command = cmd;
	waitpid(command->pid, command->w_status, 0);
}