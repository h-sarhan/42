/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/17 07:35:30 by hsarhan          ###   ########.fr       */
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
	char	*infile;
	char	**cmd_1_args;
	char	**cmd_2_args;
	int		*exit_status;

	exit_status = NULL;
	(void)exit_status; // for the compiler to shut up
	if (argc != 5)
	{
		// do something here
		ft_printf("Wrong number of arguments\n");
		return (1);
	}
	infile = argv[1];
	cmd_1_args = ft_split(argv[2], ' ');
	if (cmd_1_args == NULL)
	{
		return (1);
	}
	cmd_2_args = ft_split(argv[3], ' ');
	if (cmd_2_args == NULL)
	{
		return (1);
	}
	cmd_1_args[0] = get_full_path(cmd_1_args[0], env);
	cmd_2_args[0] = get_full_path(cmd_2_args[0], env);
	if (cmd_1_args[0] == NULL)
		perror(NULL);
		// ft_printf("DO SOMETHING\n");
	if (cmd_2_args[0] == NULL)
		perror(NULL);
		// ft_printf("DO SOMETHING\n");

	// TODO: Handle errors here
	int	in_fd = open(infile, O_RDONLY);	
	if (in_fd == -1)
	{
		// TODO: DO SOMETHING HERE
		return (1); // ??
	}
	int	pipe_fds[2];
	if (pipe(pipe_fds) == -1)
	{
		// TODO: HANDLE ERRORS
		return (1); // ??
	}
	int pid = fork();
	if (pid == -1)
	{
		// TODO: DO SOMETHING HERE
		return (1); // ??
	}
	if (pid == 0)
	{
		close(pipe_fds[READ]); // This could fail
		dup2(in_fd, 0); // This could fail
		dup2(pipe_fds[WRITE], 1); // This could fail
		execve(cmd_1_args[0], cmd_1_args, NULL);

		// if execve fails do the stuff below
		close(pipe_fds[WRITE]); // this could fail
		close(in_fd); // this could fail
		free_split_array(cmd_1_args);
		free_split_array(cmd_2_args);
		// TODO: PUT THE CORRECT EXIT CODE LATER
		exit(1); // send this exit code to the parent process
	}
	else
	{
		close(in_fd); // this could fail
		waitpid(pid, NULL, 0); // This could fail??
		pid = fork(); // this could fail
		if (pid == -1)
		{
			return (1);
		}
		if (pid == 0)
		{
			close(pipe_fds[WRITE]); // this could fail
			dup2(pipe_fds[READ], 0); // this could fail
			// TODO: CHECK THIS LATER
			int outfile = open(argv[4], O_WRONLY | O_CREAT, 0644); // this could fail
			if (outfile == -1)
			{
				return (1); // ??
			}
			dup2(outfile, 1); // this could fail
			execve(cmd_2_args[0], cmd_2_args, NULL);
			// if execve fails do the below
			close(pipe_fds[READ]); // this could fail
			close(outfile); // this could fail
			free_split_array(cmd_1_args);
			free_split_array(cmd_2_args);
			// TODO: PUT THE CORRECT EXIT CODE LATER
			exit(1); // send this to the parent process somehow could use a variable here
		}
		else
		{
			close(pipe_fds[WRITE]); // this could fail
			close(pipe_fds[READ]); //this could fail
			waitpid(pid, NULL, 0); // This could fail??
			free_split_array(cmd_1_args);
			free_split_array(cmd_2_args);
		}
	}
}
