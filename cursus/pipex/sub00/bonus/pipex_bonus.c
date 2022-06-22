/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 07:31:33 by hsarhan          ###   ########.fr       */
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
	int			pids[2];

	pids[0] = ((t_command *)commands->content)->pid;
	pids[1] = ((t_command *)ft_lstlast(commands)->content)->pid;
	last_cmd = ft_lstlast(commands)->content;
	last_cmd_valid = last_cmd->valid;
	pipex_cleanup(pipe_fds, fds, commands);
	if (pids[0] != -1)
		waitpid(pids[0], &w_status, 0);
	if (pids[1] != -1)
	waitpid(last_cmd->pid, &w_status, 0);
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
	int			fds[2];
	int			pipe_fds[2];
	// int			pids[2];
	int			i;
	t_list		*first;
	
	(void)argc;
	// TODO: CHECK ARGS WITH MULTIPLE PIPES
	// FOR NOW ASSUME PERFECT INPUT
	check_arg_count(argc);
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
	if (cmd->pid == 0)
		run_first_cmd(cmd, pipe_fds, fds, env);
	cmd = commands->next->content;
	cmd->pid = ft_fork(cmd->valid);
	if (cmd->pid == 0)
		run_last_cmd(cmd, pipe_fds, fds, env);
	wait_and_exit(pipe_fds, fds, first);
}
