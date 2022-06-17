/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/17 15:48:15 by hsarhan          ###   ########.fr       */
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

// char	*get_shell_name(char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*shell_name;

// 	i = 0;
// 	while (env[i] != NULL && ft_strncmp(env[i], "SHELL=", 6) != 0)
// 		i++;
// 	if (env[i] == NULL)
// 		return (NULL);
// 	paths = ft_split(env[i], '/');
// 	if (paths == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (paths[i] != NULL)
// 		i++;
// 	shell_name = ft_strdup(paths[i - 1]);
// 	free_split_array(paths);
// 	return (shell_name);
// }

int	main(int argc, char **argv, char **env)
{
	char	*infile;
	char	**cmd_1_args;
	char	**cmd_2_args;

	if (argc != 5)
		return (1);
	cmd_1_args = ft_split(argv[2], ' ');
	if (cmd_1_args == NULL)
	{
		// ft_split failed
		perror(argv[0]);
		return (1);
	}
	cmd_2_args = ft_split(argv[3], ' ');
	if (cmd_2_args == NULL)
	{
		// ft_split failed
		perror(argv[0]);
		return (1);
	}
	cmd_1_args[0] = get_full_path(cmd_1_args[0], env);
	if (cmd_1_args[0] == NULL)
	{
		// command 1 doesnt exist
		perror(argv[0]);
		return (1);
	}
	cmd_2_args[0] = get_full_path(cmd_2_args[0], env);
	if (cmd_2_args[0] == NULL)
	{
		// command 2 doesnt exist
		perror(argv[0]);
		return (1);
	}

	// TODO: Handle errors here
	infile = argv[1];
	int	in_fd = open(infile, O_RDONLY);	
	if (in_fd == -1)
	{
		// infile doesnt exist
		// in this case we do not end the process for some reason
		perror(argv[0]);
		// return (1);
	}
	int	pipe_fds[2];
	if (pipe(pipe_fds) == -1)
	{
		perror(argv[0]);
		// TODO: HANDLE ERRORS
		return (1); // ??
	}
	int pid = fork();
	if (pid == -1)
	{
		// TODO: DO SOMETHING HERE
		perror(argv[0]);
		return (1); // ??
	}
	if (pid == 0)
	{
		if (close(pipe_fds[READ]) == -1)
		{
			perror(argv[0]);
			return (1);
		}
		if (in_fd != -1 && dup2(in_fd, 0) == -1)
		{
			ft_printf("Duping in_fd\n");
			perror(argv[0]);
			return (1);
		}
		if (dup2(pipe_fds[WRITE], 1) == -1)
		{
			perror(argv[0]);
			return (1);
		}
		if (in_fd == -1)
		{
			int devnull = open("/dev/null", O_RDONLY);
			dup2(devnull, 0);
		}
		execve(cmd_1_args[0], cmd_1_args, NULL);
		// ft_printf("COMMAND FAILED\n");
		// if execve fails do the stuff below
		if (close(pipe_fds[WRITE]) == -1)
		{
			perror(argv[0]);
			return (1);
		}
		if (in_fd != -1 &&close(in_fd) == -1)
		{
			ft_printf("closing in_fd\n");
			perror(argv[0]);
			return (1);
		}
		free_split_array(cmd_1_args);
		free_split_array(cmd_2_args);
		// TODO: PUT THE CORRECT EXIT CODE LATER
		exit(1); // send this exit code to the parent process somehow
	}
	else
	{
		if (in_fd != -1 && close(in_fd) == -1)
		{
			ft_printf("closing in_fd\n");
			perror(argv[0]);
			return (1);
		}
		// GET EXIT CODE OF CHILD PROCESS HERE
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
