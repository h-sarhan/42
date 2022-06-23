/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:00:11 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:13:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// TODO: Check leaks with errors
// Replicates the behaviour of 
// `< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile` in bash
int	main(int argc, char **argv)
{
	t_list		*command_list;
	t_command	*cmd;
	t_list		*first;
	int			fds[2];
	int			pipe_fds[2];

	check_arg_count(argc);
	fds[0] = open_file(argv[1], 0);
	fds[1] = open_file(argv[argc - 1], 1);
	command_list = create_command_list(argc, argv, fds);
	first = command_list;
	ft_pipe(pipe_fds);
	handle_first_cmd(command_list->content, fds, pipe_fds);
	command_list = command_list->next;
	command_list = handle_mid_cmds(command_list, pipe_fds, fds);
	cmd = command_list->content;
	cmd->in_fd = pipe_fds[READ];
	cmd->out_fd = fds[1];
	cmd->pid = ft_fork(cmd->valid);
	if (cmd->pid == 0)
		run_last_cmd(cmd, pipe_fds, fds);
	wait_and_exit(pipe_fds, fds, first);
}
