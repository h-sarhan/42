/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/21 10:03:36 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_args(char *arg, char **env)
{
	char	**cmd_args;

	cmd_args = split_args(arg, ' ');
	malloc_check(cmd_args);
	if (access(cmd_args[0], X_OK) == -1)
	{
		cmd_args[0] = get_full_path(cmd_args[0], env);
		malloc_check(cmd_args[0]);
	}
	trim_args(cmd_args);
	return (cmd_args);
}

void	run_command2(int *pipe_fds, int *fds, char **cmd_args, char **env)
{
	close_fd(pipe_fds[WRITE]);
	dup_fd(pipe_fds[READ], STDIN);
	close_fd(fds[0]);
	dup_fd(fds[1], STDOUT);
	if (fds[1] != -1)
		execve(cmd_args[0], cmd_args, env);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	free_split_array(cmd_args);
	exit(1);
}

void	pipex_cleanup(int *pipe_fds, int *fds, char ***cmd_args)
{
	close_fd(pipe_fds[WRITE]);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	close_fd(fds[0]);
	free_split_array(cmd_args[1]);
}

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

int	main(int argc, char **argv, char **env)
{
	char	**cmd_args[2];
	int		cmd_valid[2];
	int		fds[2];
	int		pipe_fds[2];
	int		pids[2];

	check_arg_count(argc);
	fds[0] = open_file(argv[1], 0);
	cmd_args[0] = get_args(argv[2], env);
	cmd_valid[0] = command_check(cmd_args[0], argv[2], fds[0]);
	fds[1] = open_file(argv[4], 1);
	cmd_args[1] = get_args(argv[3], env);
	cmd_valid[1] = command_check(cmd_args[1], argv[3], fds[1]);
	ft_pipe(pipe_fds);
	pids[0] = ft_fork(cmd_valid[0]);
	if (pids[0] == 0)
		run_command(pipe_fds, fds, cmd_args[0], env);
	free_split_array(cmd_args[0]);
	pids[1] = ft_fork(cmd_valid[1]);
	if (pids[1] == 0)
		run_command2(pipe_fds, fds, cmd_args[1], env);
	pipex_cleanup(pipe_fds, fds, cmd_args);
	wait_and_exit(pids, fds[1], cmd_valid[1]);
}
