/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:14:54 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/29 10:34:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Resizes an array by mallocing an array of new_len
// and copies all elements of the old array into the new array
// Finally, the old array is freed
void	*resize(char **arr, int old_len, int new_len)
{
	int		i;
	char	*new_arr;

	i = 0;
	new_arr = malloc(new_len * sizeof(char));
	if (new_arr == NULL)
	{
		free(*arr);
		return (NULL);
	}
	while (i < old_len && i < new_len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	while (i < new_len)
		new_arr[i++] = '\0';
	return (new_arr);
}

// Reads from STDIN into a buffer until a limiter is found
// Then the buffer is returned
char	*read_from_stdin(char *limiter)
{
	char	*buff;
	int		buffer_len;
	int		i;
	char	ch;

	buffer_len = 100;
	buff = ft_calloc(buffer_len + 1, sizeof(char));
	i = 0;
	while (ft_strnstr(buff, limiter, ft_strlen(buff)) == NULL)
	{
		if (i == buffer_len)
		{
			buff = resize(&buff, buffer_len, (buffer_len * 2) + 1);
			buffer_len *= 2;
		}
		if (read(STDIN, &ch, 1) < 1)
			break ;
		buff[i] = ch;
		i++;
	}
	buff[i] = '\0';
	if (ft_strnstr(buff, limiter, ft_strlen(buff)) != NULL)
		ft_strnstr(buff, limiter, ft_strlen(buff))[1] = '\0';
	return (buff);
}

// Runs the first command followed by a here_doc
t_cmd	*run_heredoc_cmd(char **argv, char *buff, int *cmd_pipes, char **env)
{
	int		heredoc_pipes[2];
	t_cmd	*cmd;

	ft_pipe(heredoc_pipes);
	write(heredoc_pipes[WRITE], buff, ft_strlen(buff));
	cmd = create_command(argv[3], env);
	cmd->valid = command_check(cmd->cmd_args, argv[3], 1);
	cmd->pid = ft_fork(1);
	if (cmd->pid == 0)
	{
		close_fd(cmd_pipes[READ]);
		close_fd(heredoc_pipes[WRITE]);
		dup_fd(heredoc_pipes[READ], STDIN);
		dup_fd(cmd_pipes[WRITE], STDOUT);
		if (cmd->valid)
			execve(cmd->cmd_args[0], cmd->cmd_args, env);
		close_fd(heredoc_pipes[READ]);
		close_fd(cmd_pipes[WRITE]);
		free_cmd(cmd);
		ft_free(buff);
		exit(EXIT_FAILURE);
	}
	close_fd(heredoc_pipes[WRITE]);
	close_fd(heredoc_pipes[READ]);
	return (cmd);
}

// Handles here_doc behaviour
t_list	*handle_here_doc(char **argv, int *cmd_pipes, int *fds, char **env)
{
	char	*limiter;
	char	*buff;
	t_cmd	*cmd;
	t_list	*cmds;
	int		argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	ft_pipe(cmd_pipes);
	fds[0] = -1;
	fds[1] = open_file(argv[argc - 1], 3);
	limiter = argv[2];
	limiter = ft_strjoinfree("\n", limiter, 0);
	limiter = ft_strjoinfree(limiter, "\n", 1);
	buff = read_from_stdin(limiter);
	cmd = run_heredoc_cmd(argv, buff, cmd_pipes, env);
	cmds = create_command_list(argc, argv, fds, env);
	free_cmd(cmds->content);
	cmds->content = cmd;
	ft_free(limiter);
	ft_free(buff);
	return (cmds);
}
