/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 14:36:08 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_full_path(char *bin, char **env)
{
	int i;
	char *path;
	char **paths;

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
			break;
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
	// cmd_valid = command_check(cmd_args, argv[2], NULL, in_fd);
	trim_args(cmd_args);
	return (cmd_args);
}

// TODO: REWRITE EVERYTHING
// TODO: REMOVE UNECESSARY INCLUDES
int main(int argc, char **argv, char **env)
{
	char	**cmd_1_args;
	char	**cmd_2_args;
	int		devnull_fd;
	int		cmd_1_valid;
	int		cmd_2_valid;
	int		w_status;
	int		in_fd;
	int		out_fd;
	int		pipe_fds[2];
	int		pid1;
	int		pid2;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	in_fd = open_file(argv[1], 0);

	cmd_1_args = get_args(argv[2], env); // checking command 1
	cmd_1_valid = command_check(cmd_1_args, argv[2], in_fd);
	
	ft_pipe(pipe_fds);
	devnull_fd = open_file("/dev/null", 0);

	// fork_command function
	pid1 = -1;
	if (cmd_1_valid)
	{
		pid1 = fork();
		fork_check(pid1);
	}
	if (pid1 == 0)
	{
		close_fd(pipe_fds[READ]);
		if (in_fd == -1)
			dup_fd(devnull_fd, STDIN);
		else
			dup_fd(in_fd, STDIN);
		dup_fd(pipe_fds[WRITE], STDOUT);
		if (cmd_1_valid && in_fd != -1)
			execve(cmd_1_args[0], cmd_1_args, env);
		// if execve fails do the stuff below
		close_fd(pipe_fds[WRITE]);
		if (in_fd != -1)
			close_fd(in_fd);
		close_fd(devnull_fd);
		free_split_array(cmd_1_args);
		// free_split_array(cmd_2_args);
		exit(1);
	}
	if (in_fd != -1)
		close_fd(in_fd);

	out_fd = open_file(argv[4], 1);

	// checking command 2
	cmd_2_args = get_args(argv[3], env);
	cmd_2_valid = command_check(cmd_2_args, argv[3], out_fd);

	// fork_command function
	pid2 = -1;
	if (cmd_2_valid)
	{
		pid2 = fork();
		fork_check(pid2);
	}

	if (pid2 == 0)
	{
		close_fd(pipe_fds[WRITE]);
		dup_fd(pipe_fds[READ], STDIN);
		dup_fd(out_fd, STDOUT);
		if (out_fd != -1)
			execve(cmd_2_args[0], cmd_2_args, env);
		// if execve fails do the below
		// cleanup
		close_fd(pipe_fds[READ]);
		if (out_fd != -1)
			close_fd(out_fd);
		close_fd(devnull_fd);
		free_split_array(cmd_1_args);
		free_split_array(cmd_2_args);
		exit(1);
	}
	// cleanup
	close_fd(pipe_fds[WRITE]);
	close_fd(pipe_fds[READ]);
	if (out_fd != -1)
		close_fd(out_fd);
	close_fd(devnull_fd);
	free_split_array(cmd_1_args);
	free_split_array(cmd_2_args);
	if (pid1 != -1)
		waitpid(pid1, &w_status, 0);
	if (pid2 != -1)
		waitpid(pid2, &w_status, 0);
	if (out_fd == -1)
		exit(1);
	if (!cmd_2_valid)
		exit(127);
	exit(WEXITSTATUS(w_status));
}

