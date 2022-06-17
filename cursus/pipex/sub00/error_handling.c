/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:52:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/17 18:21:02 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	malloc_check(void *mem)
{
	if (mem == NULL)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

void	fd_check(int fd, char *file_name)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(file_name, 2);
	}
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
