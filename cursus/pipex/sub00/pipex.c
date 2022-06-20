/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 13:31:54 by hsarhan          ###   ########.fr       */
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

// TODO: HANDLE ARGUMENTS IN QUOTATION MARKS
// TODO: CREATE FILE_CHECK FUNCTION TO CHECK FILE PERMISSIONS
// if (errno == ENOACCESS) Permission denied
// TODO: USE strerror with strjoin
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

	// checking command 1
	// check command_function
	cmd_1_args = split_args(argv[2], ' ');
	malloc_check(cmd_1_args);
	if (access(cmd_1_args[0], X_OK) == -1)
	{
		cmd_1_args[0] = get_full_path(cmd_1_args[0], env);
		malloc_check(cmd_1_args[0]);
	}
	cmd_1_valid = command_check(cmd_1_args, argv[2], NULL, in_fd);
	trim_args(cmd_1_args);

	out_fd = open_file(argv[4], 1);

	// checking command 2
	// check command_function
	cmd_2_args = split_args(argv[3], ' ');
	malloc_check(cmd_2_args);
	if (access(cmd_2_args[0], X_OK) == -1)
	{
		cmd_2_args[0] = get_full_path(cmd_2_args[0], env);
		malloc_check(cmd_2_args[0]);
	}
	cmd_2_valid = command_check(cmd_2_args, argv[3], NULL, out_fd);

	trim_args(cmd_2_args);

	// Create pipe function
	pipe_check(pipe(pipe_fds));
	devnull_fd = open_file("/dev/null", 0);
	// fd_check(devnull_fd, "/dev/null");

	// fork_command function
	pid1 = -1;
	if (cmd_1_valid)
	{
		pid1 = fork();
		fork_check(pid1);
	}

	// fork command function
	if (pid1 == 0)
	{
		close_fd(pipe_fds[READ]);
		close_fd(out_fd);
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
		free_split_array(cmd_2_args);
		exit(1);
	}
	// else
	// {
	if (in_fd != -1)
		close_fd(in_fd);

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
		// ft_putendl_fd(cmd_2_args[0], 2);
		// ft_putendl_fd(cmd_2_args[1], 2);
		// ft_putendl_fd(cmd_2_args[2], 2);
		if (cmd_2_valid && out_fd != -1)
			execve(cmd_2_args[0], cmd_2_args, env);
		// if execve fails do the below
		// cleanup
		close_fd(pipe_fds[READ]);
		close_fd(out_fd);
		close_fd(devnull_fd);
		free_split_array(cmd_1_args);
		free_split_array(cmd_2_args);
		exit(1);
	}
	// cleanup
	close_fd(pipe_fds[WRITE]);
	close_fd(pipe_fds[READ]);
	close_fd(out_fd);
	close_fd(devnull_fd);
	free_split_array(cmd_1_args);
	free_split_array(cmd_2_args);
	if (pid1 != -1)
		waitpid(pid1, &w_status, 0);
	if (pid2 != -1)
		waitpid(pid2, &w_status, 0);
	if (!cmd_2_valid)
		exit(127);
	if (WIFEXITED(w_status))
		exit(WEXITSTATUS(w_status));
	exit(0);
}

