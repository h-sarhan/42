/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 09:59:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Closes file descrtiptors and frees allocated memory
void	pipex_cleanup(int *pipe_fds, int *fds, t_list *commands)
{
	close_fd(pipe_fds[WRITE]);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	close_fd(fds[0]);
	ft_lstclear(&commands, free_cmd);
}

// Waits for the given pids and exits the program 
// with an appropriate exit code
void	wait_and_exit(int *pipe_fds, int *fds, t_list *commands)
{
	int			w_status;
	t_command	*last_cmd;
	int			last_cmd_valid;

	(void)pipe_fds;
	close_fd(pipe_fds[WRITE]);
	last_cmd = ft_lstlast(commands)->content;
	last_cmd_valid = last_cmd->valid;
	
	ft_lstiter(commands, wait_cmd);
	ft_lstclear(&commands, free_cmd);
	if (fds[1] == -1)
		exit(1);
	if (!last_cmd_valid)
		exit(127);
	exit(WEXITSTATUS(w_status));
}


// TODO: Check leaks with errors
// Replicates the behaviour of 
// `< infile cmd1 | cmd2 > outfile` in bash
int	main(int argc, char **argv, char **env)
{
	t_list		*commands;
	t_command	*cmd;
	t_list		*first;
	int			fds[2];
	int			pipe_fds[2];
	int			i;

	(void)argc;
	// TODO: CHECK ARGS WITH MULTIPLE PIPES
	// FOR NOW ASSUME PERFECT INPUT
	// check_arg_count(argc);
	commands = NULL;
	fds[0] = open_file(argv[1], 0);
	cmd = create_command(argv[2], env);
	cmd->valid = command_check(cmd->cmd_args, argv[2], fds[0]);
	ft_lstadd_back(&commands, ft_lstnew(cmd));
	first = commands;
	i = 3;
	while (i < argc - 2)
	{
		cmd = create_command(argv[i], env);
		cmd->valid = command_check(cmd->cmd_args, argv[i], 0);
		ft_lstadd_back(&commands, ft_lstnew(cmd));
		i++;
	}
	fds[1] = open_file(argv[argc - 1], 1);
	cmd = create_command(argv[argc - 2], env);
	cmd->valid = command_check(cmd->cmd_args, argv[argc - 2], fds[1]);
	ft_lstadd_back(&commands, ft_lstnew(cmd));
	ft_pipe(pipe_fds);
	cmd = commands->content;
 	cmd->pid = ft_fork(cmd->valid);
	cmd->in_fd = fds[0];
	cmd->out_fd = pipe_fds[WRITE];
	if (cmd->pid == 0)
		run_first_cmd(cmd, pipe_fds, fds, env);
	commands = commands->next;
	while (commands->next != NULL)
	{
		close_fd(pipe_fds[WRITE]);
		cmd = commands->content;
		cmd->in_fd = pipe_fds[READ];
		ft_pipe(pipe_fds);
		cmd->out_fd = pipe_fds[WRITE];
		cmd->pid = ft_fork(cmd->valid);
		if (cmd->pid == 0)
			run_middle_cmd(cmd, pipe_fds, fds, env);
		commands = commands->next;
	}
	cmd = commands->content;
	cmd->in_fd = pipe_fds[READ];
	cmd->out_fd = fds[1];
	cmd->pid = ft_fork(cmd->valid);
	if (cmd->pid == 0)
		run_last_cmd(cmd, pipe_fds, fds, env);
	wait_and_exit(pipe_fds, fds, first);
}
