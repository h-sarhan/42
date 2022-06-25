/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:14:54 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/25 12:29:33 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (read(STDIN, &ch, 1) == 0)
			break ;
		buff[i] = ch;
		i++;
	}
	ft_strnstr(buff, limiter, ft_strlen(buff))[0] = '\0';
	return (buff);
}

t_command	*run_heredoc_cmd(char **argv, char *buff, int *cmd_pipes)
{
	int			heredoc_pipes[2];
	t_command	*cmd;

	ft_pipe(heredoc_pipes);
	write(heredoc_pipes[WRITE], buff, ft_strlen(buff));
	cmd = create_command(argv[3]);
	cmd->valid = command_check(cmd->cmd_args, argv[3], 1);
	cmd->pid = ft_fork(1);
	if (cmd->pid == 0)
	{
		close_fd(cmd_pipes[READ]);
		close_fd(heredoc_pipes[WRITE]);
		dup_fd(heredoc_pipes[READ], STDIN);
		dup_fd(cmd_pipes[WRITE], STDOUT);
		if (cmd->valid)
			execve(cmd->cmd_args[0], cmd->cmd_args, environ);
		close_fd(heredoc_pipes[READ]);
		close_fd(cmd_pipes[WRITE]);
		free_cmd(cmd);
		ft_free(buff);
		exit(EXIT_FAILURE);
	}
	close_fd(heredoc_pipes[WRITE]);
	close_fd(heredoc_pipes[READ]);
	// close_fd(cmd_pipes[WRITE]);
	return (cmd);
}

t_command	*run_heredoc_cmd1(char **argv, int *cmd_pipes, char *buff,
	t_command *cmd)
{
	t_command	*cmd1;
	int			out_fd;

	cmd1 = create_command(argv[4]);
	cmd1->valid = command_check(cmd1->cmd_args, argv[4], 1);
	out_fd = open_file(argv[5], 3);
	cmd1->pid = ft_fork(1);
	if (cmd1->pid == 0)
	{
		dup_fd(cmd_pipes[READ], STDIN);
		dup_fd(out_fd, STDOUT);
		if (cmd1->valid)
			execve(cmd1->cmd_args[0], cmd1->cmd_args, environ);
		close_fd(out_fd);
		close_fd(cmd_pipes[READ]);
		ft_free(buff);
		free_cmd(cmd);
		free_cmd(cmd1);
		exit(EXIT_FAILURE);
	}
	close_fd(out_fd);
	close_fd(cmd_pipes[READ]);
	return (cmd1);
}

t_command	*handle_here_doc(int argc, char **argv, int *cmd_pipes)
{
	char		*limiter;
	char		*buff;
	// t_command	*cmds[2];
	t_command		*cmd;

	if (argc < 6)
	{
		ft_putstr_fd("Wrong number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	limiter = argv[2];
	buff = read_from_stdin(limiter);
	cmd = run_heredoc_cmd(argv, buff, cmd_pipes);
	// cmds[1] = run_heredoc_cmd1(argv, cmd_pipes, buff, cmds[0]);
	ft_free(buff);
	return (cmd);
	// wait_cmd(cmds[0]);
	// wait_cmd(cmds[1]);
	// free_cmd(cmds[0]);
	// free_cmd(cmds[1]);
	// exit(EXIT_SUCCESS);
}
