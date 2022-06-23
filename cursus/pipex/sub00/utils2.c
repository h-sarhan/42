/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:46:59 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:33:50 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Wrapper around free to avoid freeing NULL
void	ft_free(void *mem)
{
	if (mem != NULL)
		free(mem);
}

// Wrapper around dup2 that handles errors when duping file desriptors
void	dup_fd(int fd_1, int fd_2)
{
	int	dup_ret;

	if (fd_1 != -1)
	{
		dup_ret = dup2(fd_1, fd_2);
		if (dup_ret == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
}

// Wrapper around close that handles errors when closing file descriptors
void	close_fd(int fd)
{
	int	close_ret;

	if (fd != -1)
	{
		close_ret = close(fd);
		if (close_ret == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
	// ft_putstr_fd("CLOSING FD: ", 2);
	// ft_putnbr_fd(fd, 2);
	// ft_putchar_fd('\n', 2);
}

// Opens a file either for writing or reading and handles errors.
// Returns a file descriptor
int	open_file(char *file_path, int outfile)
{
	int		mode;
	int		fd;

	fd = 1;
	mode = R_OK;
	if (outfile == 1)
		mode = W_OK;
	if (outfile == 0 && access(file_path, mode) == -1)
		fd = -1;
	else if (outfile == 1)
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		print_error_string(strerror(errno), file_path);
		return (-1);
	}
	return (fd);
}

// Splits cmd1 or cmd2 into arguments that can be used by execve.
// Also expands the binary of a command into its full path.
// If the PATH variable cannot be found in the environment variables
// then a default PATH compatible with most UNIX based systems will be used
char	**get_args(char *arg)
{
	char	**cmd_args;
	int		i;
	char	**env;

	env = environ;
	cmd_args = split_args(arg, ' ');
	malloc_check(cmd_args);
	if (access(cmd_args[0], X_OK) == -1)
	{
		i = 0;
		while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		if (env[i] == NULL)
		{
			env = ft_split("PATH=/usr/bin:/bin:/usr/sbin:/sbin", ' ');
			malloc_check(env);
			i = -1;
		}
		cmd_args[0] = get_full_path(cmd_args[0], env);
		malloc_check(cmd_args[0]);
		if (i == -1)
			free_split_array(env);
	}
	trim_args(cmd_args);
	return (cmd_args);
}
