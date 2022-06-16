/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/16 19:28:45 by hsarhan          ###   ########.fr       */
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
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], bin);
		if (access(path, X_OK) != -1)
			break ;
		free(path);
		i++;
	}
	if (paths[i] == NULL)
		path = NULL;
	free(bin);
	free_split_array(paths);
	return (path);
}


int	main(int argc, char **argv, char **env)
{
	char	*infile;
	char	**cmd_1_args;
	char	**cmd_2_args;
	
	infile = argv[1];
	cmd_1_args = ft_split(argv[2], ' ');
	cmd_2_args = ft_split(argv[3], ' ');
	cmd_1_args[0] = get_full_path(cmd_1_args[0], env);
	cmd_2_args[0] = get_full_path(cmd_2_args[0], env);
	if (cmd_1_args == NULL)
		ft_printf("DO SOMETHING\n");
	if (cmd_2_args == NULL)
		ft_printf("DO SOMETHING\n");
	int	in_fd = open(infile, O_RDONLY);	
	int	pipe_fds[2];
	pipe(pipe_fds);
	int pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[READ]);
		dup2(in_fd, 0);
		dup2(pipe_fds[WRITE], 1);
		execve(cmd_1_args[0], cmd_1_args, NULL);
		close(pipe_fds[WRITE]);
		close(in_fd);
		free_split_array(cmd_1_args);
		free_split_array(cmd_2_args);
		// TODO: PUT THE CORRECT EXIT CODE LATER
		exit(1);
	}
	else
	{
		close(in_fd);
		waitpid(pid, NULL, 0);
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fds[WRITE]);
			dup2(pipe_fds[READ], 0);
			// TODO: CHECK THIS LATER
			int outfile = open(argv[4], O_WRONLY | O_CREAT, 0644);
			dup2(outfile, 1);
			execve(cmd_2_args[0], cmd_2_args, NULL);
			close(pipe_fds[READ]);
			free_split_array(cmd_1_args);
			free_split_array(cmd_2_args);
			close(outfile);
			// TODO: PUT THE CORRECT EXIT CODE LATER
			exit(1);
		}
		else
		{
			close(pipe_fds[WRITE]);
			close(pipe_fds[READ]);
			wait(NULL);
			free_split_array(cmd_1_args);
			free_split_array(cmd_2_args);
		}
	}
}