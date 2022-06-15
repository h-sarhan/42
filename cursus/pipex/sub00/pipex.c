/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 16:28:03 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	*get_full_path(char *bin)
{
	// TODO: CHECK FOR ERRORS
	char	**args;
	char	*joined_str;
	int		fd[2];
	char	*buff;
	
	pipe(fd);
	int pid = fork();
	buff = NULL;
	if (pid == 0)
	{
		close(fd[READ]);
		joined_str = ft_strjoin("/usr/bin/whereis ", bin);
		args = ft_split(joined_str, ' ');
		free(joined_str);
		dup2(fd[WRITE], 1);
		execve("/usr/bin/whereis", args, NULL);
		free(args);
		close(fd[WRITE]);
	}
	else
	{
		buff = ft_calloc(1000, sizeof(char));
		close(fd[WRITE]);
		read(fd[READ], buff, 999);
		close(fd[READ]);
		waitpid(pid, NULL, 0);
	}
	char	*buff_trimmed = ft_strtrim(buff, "\n");
	free(buff);
	return (buff_trimmed);
}


int	main(int argc, char **argv)
{
	// TODO: CHECK FOR ERRORS
	(void)argc;
	(void)argv;
	char	*infile = argv[1];
	char	**cmd_1_args = ft_split(argv[2], ' ');
	char	*cmd_1 = cmd_1_args[0];

	if (access(cmd_1_args[0], F_OK) == -1)
	{
		cmd_1_args[0] = get_full_path(cmd_1_args[0]);
		free(cmd_1);
	}
	int	in_fd = open(infile, O_RDONLY);	
	int pid = fork();
	if (pid == 0)
	{
		dup2(in_fd, 0);
		execve(cmd_1_args[0], cmd_1_args, NULL);
	}
	else
	{
		close(in_fd);
		waitpid(pid, NULL, 0);
	}
}