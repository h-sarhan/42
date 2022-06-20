/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:52:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/20 11:15:02 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO: CREATE FILE_CHECK FUNCTION TO CHECK FILE PERMISSIONS
// if (errno == ENOACCESS) Permission denied
// TODO: USE strerror with strjoinZ

void	malloc_check(void *mem)
{
	if (mem == NULL && errno == ENOMEM)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

int	open_file(char *file_path, int outfile)
{
	char	*str;
	int		mode;
	int		fd;
	
	fd = 1;
	mode = R_OK;
	if (outfile == 1)
		mode = W_OK;
	if (outfile != 1 && access(file_path, mode) == -1)
		fd = -1;
	else if (outfile == 1)
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		str = ft_strjoin("pipex: ", strerror(errno));
		str = ft_strjoinfree(str, file_path, 1);
		ft_putendl_fd(str, 2);
		ft_free(str);
		return (-1);
	}
	return (fd);
}

int command_check(char **cmd_args, char *arg_list, int *exit_code, int fd)
{
	char	**args;
	char	*cmd_name;
	int		i;

	if (cmd_args[0] == NULL && errno == ENOENT)
	{
		args = ft_split(arg_list, ' ');
		malloc_check(args);
		cmd_name = ft_strdup(args[0]);
		malloc_check(cmd_name);
		free_split_array(args);
		if (fd != -1)
		{
			if (ft_strchr(cmd_name, '/') == NULL)
			{
				ft_putstr_fd("pipex: command not found: ", 2);
				ft_putendl_fd(cmd_name, 2);
			}
			// else
			// 	fd_check(-1, cmd_name);
		}
		ft_free(cmd_name);
		if (exit_code != NULL)
			*exit_code = 127;
		i = 0;
		while (cmd_args[++i] != NULL)
			ft_free(cmd_args[i]);
		return (0);
	}
	return (1);
}

void	pipe_check(int pipe_ret)
{
	if (pipe_ret == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

void	fork_check(int pid)
{
	if (pid == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
