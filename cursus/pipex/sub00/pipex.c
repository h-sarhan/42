/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/18 11:04:38 by hsarhan          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	**cmd_1_args;
	char	**cmd_2_args;
	int		devnull_fd;
	int		cmd_1_valid;
	int		cmd_2_valid;
	
	devnull_fd = open("/dev/null", O_RDONLY);
	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	cmd_1_args = ft_split(argv[2], ' ');
	malloc_check(cmd_1_args);
	cmd_1_args[0] = get_full_path(cmd_1_args[0], env);
	malloc_check(cmd_1_args[0]);
	cmd_1_valid = command_check(cmd_1_args, argv[2]);

	int	in_fd = open(argv[1], O_RDONLY);	
	fd_check(in_fd, argv[1], cmd_1_valid); 

	cmd_2_args = ft_split(argv[3], ' ');
	malloc_check(cmd_2_args);
	cmd_2_args[0] = get_full_path(cmd_2_args[0], env);
	malloc_check(cmd_2_args[0]);
	cmd_2_valid = command_check(cmd_2_args, argv[3]);

	int out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); // this could fail
	fd_check(out_fd, argv[4], cmd_2_valid);

	int	pipe_fds[2];
	pipe_check(pipe(pipe_fds));

	int	pid = fork();
	fork_check(pid);

	if (pid == 0)
	{
		close_fd(pipe_fds[READ]);
		if (in_fd == -1)
			dup_fd(devnull_fd, STDIN);
		else
			dup_fd(in_fd, STDIN);
		dup_fd(pipe_fds[WRITE], STDOUT);
		if (cmd_1_valid)
			execve(cmd_1_args[0], cmd_1_args, NULL);
		// if execve fails do the stuff below
		close_fd(pipe_fds[WRITE]);
		if (in_fd != -1)
			close_fd(in_fd);
		free_split_array(cmd_1_args);
		free_split_array(cmd_2_args);
		exit(1);
	}
	else
	{
		if (in_fd != -1)
			close_fd(in_fd);
		waitpid(pid, NULL, 0); // This could fail??
		pid = fork(); // this could fail
		fork_check(pid);
		if (pid == 0)
		{
			close_fd(pipe_fds[WRITE]); // this could fail
			dup_fd(pipe_fds[READ], STDIN); // this could fail
			dup_fd(out_fd, STDOUT); // this could fail
			if (cmd_2_args[0] != NULL)
				execve(cmd_2_args[0], cmd_2_args, NULL);
			// if execve fails do the below
			close_fd(pipe_fds[READ]); // this could fail
			close_fd(out_fd); // this could fail
			free_split_array(cmd_1_args);
			free_split_array(cmd_2_args);
			// TODO: PUT THE CORRECT EXIT CODE LATER
			exit(1); // send this to the parent process somehow could use a variable here
		}
		else
		{
			close_fd(pipe_fds[WRITE]); // this could fail
			close_fd(pipe_fds[READ]); //this could fail
			waitpid(pid, NULL, 0); // This could fail??
			free_split_array(cmd_1_args);
			free_split_array(cmd_2_args);
		}
	}
}
