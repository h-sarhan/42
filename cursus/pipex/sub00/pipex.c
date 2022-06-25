/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:42:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Waits for the given pids and exits the program 
// with an appropriate exit code
void	wait_and_exit(int *pipe_fds, int *fds, t_list *command_list)
{
	t_cmd	*last_cmd;
	int		last_cmd_valid;
	int		w_status;

	close_fd(pipe_fds[READ]);
	close_fd(fds[0]);
	close_fd(fds[1]);
	last_cmd = ft_lstlast(command_list)->content;
	last_cmd_valid = last_cmd->valid;
	ft_lstiter(command_list, wait_cmd);
	w_status = last_cmd->w_status;
	ft_lstclear(&command_list, free_cmd);
	if (fds[1] == -1)
		exit(1);
	if (!last_cmd_valid)
		exit(127);
	exit(WEXITSTATUS(w_status));
}

// Creates a linked list of commands
t_list	*create_command_list(int argc, char **argv, int *fds, int hd)
{
	t_list	*command_list;
	t_cmd	*cmd;
	int		i;
	t_list	*cmd_el;

	command_list = NULL;
	i = 2;
	if (hd == 1)
		i = 3;
	while (i < argc - 1)
	{
		cmd = create_command(argv[i]);
		if (i == 2)
			cmd->valid = command_check(cmd->cmd_args, argv[i], fds[0]);
		else if (i == argc - 2)
			cmd->valid = command_check(cmd->cmd_args, argv[i], fds[1]);
		else
			cmd->valid = command_check(cmd->cmd_args, argv[i], 0);
		cmd_el = ft_lstnew(cmd);
		malloc_check(cmd_el);
		ft_lstadd_back(&command_list, cmd_el);
		i++;
	}
	return (command_list);
}

// Creates a child process for the first command and runs that command
void	handle_first_cmd(t_cmd *cmd, int *fds, int *pipe_fds, t_list *cmds)
{
	cmd->in_fd = fds[0];
	cmd->out_fd = pipe_fds[WRITE];
	cmd->pid = ft_fork(cmd->valid);
	if (cmd->pid == 0)
		run_first_cmd(cmd, pipe_fds, fds, cmds);
}

// Creates a child process for all the middle commands and runs those commands
t_list	*handle_mid_cmds(t_list *cmd_list, int *pipes, int *fds, t_list *cmds)
{
	t_cmd	*cmd;

	while (cmd_list->next != NULL)
	{
		close_fd(pipes[WRITE]);
		cmd = cmd_list->content;
		cmd->in_fd = pipes[READ];
		ft_pipe(pipes);
		cmd->out_fd = pipes[WRITE];
		cmd->pid = ft_fork(cmd->valid);
		if (cmd->pid == 0)
			run_middle_cmd(cmd, pipes, fds, cmds);
		cmd_list = cmd_list->next;
		close_fd(cmd->in_fd);
	}
	close_fd(pipes[WRITE]);
	return (cmd_list);
}

// Creates a child process for the last command and runs that command
void	handle_last_cmd(t_cmd *cmd, int *fds, int *pipe_fds, t_list *first)
{
	cmd->in_fd = pipe_fds[READ];
	cmd->out_fd = fds[1];
	cmd->pid = ft_fork(cmd->valid);
	if (cmd->pid == 0)
		run_last_cmd(cmd, pipe_fds, fds, first);
	wait_and_exit(pipe_fds, fds, first);
}
