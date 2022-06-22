/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 06:16:36 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// // Runs the command to the left of the pipe.
// // If the infile file descriptor is invalid then it will be replaced
// // with the "/dev/null" file descriptor which will return the EOF character
// // when it is read from.
// void	run_command(int *pipe_fds, int *fds, char **cmd_args, char **env)
// {
// 	int	null_fd;

// 	null_fd = open_file("/dev/null", 0);
// 	close_fd(pipe_fds[READ]);
// 	close_fd(fds[1]);
// 	if (fds[0] == -1)
// 		dup_fd(null_fd, STDIN);
// 	else
// 		dup_fd(fds[0], STDIN);
// 	dup_fd(pipe_fds[WRITE], STDOUT);
// 	if (fds[0] != -1)
// 		execve(cmd_args[0], cmd_args, env);
// 	close_fd(pipe_fds[WRITE]);
// 	close_fd(fds[0]);
// 	close_fd(null_fd);
// 	// free_split_array(cmd_args[0]);
// 	// free_split_array(cmd_args[1]);
// 	exit(1);
// }

// Runs the command to the right of the pipe
// void	run_command2(int *pipe_fds, int *fds, char **cmd_args, char **env)
// {
// 	close_fd(pipe_fds[WRITE]);
// 	close_fd(fds[0]);
// 	dup_fd(pipe_fds[READ], STDIN);
// 	dup_fd(fds[1], STDOUT);
// 	if (fds[1] != -1)
// 		execve(cmd_args[0], cmd_args, env);
// 	close_fd(pipe_fds[READ]);
// 	close_fd(fds[1]);
// 	// free_split_array(cmd_args[1]);
// 	exit(1);
// }

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
void	wait_and_exit(int *pids, int out_fd, int cmd_2_valid)
{
	int	w_status;

	if (pids[0] != -1)
		waitpid(pids[0], &w_status, 0);
	if (pids[1] != -1)
		waitpid(pids[1], &w_status, 0);
	if (out_fd == -1)
		exit(1);
	if (!cmd_2_valid)
		exit(127);
	exit(WEXITSTATUS(w_status));
}

// Replicates the behaviour of 
// `< infile cmd1 | cmd2 > outfile` in bash
int	main(int argc, char **argv, char **env)
{
	t_list		*commands;
	t_command	*cmd;
	// t_command	*commands[2];
	int			fds[2];
	int			pipe_fds[2];
	int			pids[2];

	check_arg_count(argc);
	commands = NULL;
	fds[0] = open_file(argv[1], 0);
	cmd = create_command(argv[2], env);
	// commands[0] = create_command(argv[2], env);
	cmd->valid = command_check(cmd->cmd_args, argv[2], fds[0]);
	ft_lstadd_back(&commands, ft_lstnew(cmd));
	fds[1] = open_file(argv[4], 1);

	cmd = create_command(argv[3], env);
	cmd->valid = command_check(cmd->cmd_args, argv[3], fds[1]);
	ft_lstadd_back(&commands, ft_lstnew(cmd));
	ft_pipe(pipe_fds);
	cmd = commands->content;
	pids[0] = ft_fork(cmd->valid);
	if (pids[0] == 0)
		run_first_cmd(cmd, pipe_fds, fds, env);
	cmd = commands->next->content;
	pids[1] = ft_fork(cmd->valid);
	if (pids[1] == 0)
		run_last_cmd(cmd, pipe_fds, fds, env);
	pipex_cleanup(pipe_fds, fds, commands);
	wait_and_exit(pids, fds[1], cmd->valid);
}
