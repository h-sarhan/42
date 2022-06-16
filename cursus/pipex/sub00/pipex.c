/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/16 11:34:26 by hsarhan          ###   ########.fr       */
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
	bin = ft_strjoin("/", bin);
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
	// TODO: CHECK FOR ERRORS
	(void)argc;
	(void)argv;
	char	*infile = argv[1];
	// TODO: ERROR HANDLING
	char	**cmd_1_args = ft_split(argv[2], ' ');
	char	*cmd_1 = cmd_1_args[0];
	char	**cmd_2_args = ft_split(argv[3], ' ');
	char	*cmd_2 = cmd_2_args[0];
	
	cmd_1 = get_full_path(cmd_1, env);
	cmd_2 = get_full_path(cmd_2, env);
	
	// TODO: ERROR HANDLING
	// THIS COULD RETURN NULL
	if (cmd_1 == NULL)
		ft_printf("DO SOMETHING\n");
	if (cmd_2 == NULL)
		ft_printf("DO SOMETHING\n");
		
	ft_printf("%s\n", cmd_1);
	ft_printf("%s\n", cmd_2);
	free_split_array(cmd_1_args);
	free_split_array(cmd_2_args);
	free(cmd_1);
	free(cmd_2);
	// int	pipe_fds[2];
	// pipe(pipe_fds);
	// if (access(cmd_1_args[0], F_OK) == -1)
	// {
	// 	cmd_1_args[0] = get_full_path(cmd_1_args[0]);
	// 	free(cmd_1);
	// }
	// // if (access(cmd_2_args[0], F_OK) == -1)
	// // {
	// // 	cmd_2_args[0] = get_full_path(cmd_2_args[0]);
	// // 	free(cmd_2);
	// // }
	// int	in_fd = open(infile, O_RDONLY);	
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	// close(pipe_fds[READ]);
	// 	dup2(in_fd, 0);
	// 	// dup2(pipe_fds[WRITE], 1);
	// 	execve(cmd_1_args[0], cmd_1_args, NULL);
	// }
	// else
	// {
	// 	close(in_fd);
	// 	waitpid(pid, NULL, 0);
	// }
	// char *buff = ft_calloc(1001, sizeof(char));
	// pid = fork();
	// if (pid == 0)
	// {
		// close(pipe_fds[WRITE]);
		// read(pipe_fds[READ], buff, 1001);
	// 	execve(cmd_2_args[0], cmd_2_args, NULL);
	// }
	// else
	// {
	// 	// printf("BUFFER IS: %s\n", buff);
	// 	waitpid(pid, NULL, 0);
	// }
}