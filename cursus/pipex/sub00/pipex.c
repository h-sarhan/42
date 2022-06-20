/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 16:52:17 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_full_path(char *bin, char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
	i = 0;
	bin = ft_strjoinfree("/", bin, 2);
	while (bin != NULL && paths != NULL && paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], bin);
		if (path == NULL || access(path, X_OK) != -1)
			break ;
		ft_free(path);
		i++;
	}
	if (bin == NULL || paths == NULL || paths[i] == NULL)
		path = NULL;
	ft_free(bin);
	free_split_array(paths);
	return (path);
}

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

void	run_command2(int *pipe_fds, int fd, char **cmd_args, char **env)
{
	close_fd(pipe_fds[WRITE]);
	dup_fd(pipe_fds[READ], STDIN);
	dup_fd(fd, STDOUT);
	if (fd != -1)
		execve(cmd_args[0], cmd_args, env);
	close_fd(pipe_fds[READ]);
	if (fd != -1)
		close_fd(fd);
	free_split_array(cmd_args);
	exit(1);
}

void	pipex_cleanup(int *pipe_fds, int *fds, char ***cmd_args)
{
	close_fd(pipe_fds[WRITE]);
	close_fd(pipe_fds[READ]);
	close_fd(fds[1]);
	free_split_array(cmd_args[1]);
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
		run_command(pipe_fds, fds[0], cmd_args[0], env);
	close_fd(fds[0]);
	free_split_array(cmd_args[0]);
	pids[1] = ft_fork(cmd_valid);
	if (pids[1] == 0)
		run_command2(pipe_fds, fds[1], cmd_args[1], env);
	pipex_cleanup(pipe_fds, fds, cmd_args);
	wait_and_exit(pids, fds[1], cmd_valid[1]);
}
