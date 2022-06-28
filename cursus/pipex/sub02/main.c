/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:00:11 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:42:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Replicates the behaviour of 
// `< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile` in bash
int	main(int argc, char **argv)
{
	t_list	*command_list;
	t_cmd	*cmd;
	t_list	*first;
	int		fds[2];
	int		pipe_fds[2];

	if (argc >= 2 && ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		command_list = handle_here_doc(argc, argv, pipe_fds, fds);
	else
	{
		check_arg_count(argc);
		fds[0] = open_file(argv[1], 0);
		fds[1] = open_file(argv[argc - 1], 1);
		command_list = create_command_list(argc, argv, fds, 0);
		cmd = command_list->content;
		ft_pipe(pipe_fds);
		handle_first_cmd(cmd, fds, pipe_fds, command_list);
	}
	first = command_list;
	command_list = command_list->next;
	command_list = handle_mid_cmds(command_list, pipe_fds, fds, first);
	cmd = command_list->content;
	handle_last_cmd(cmd, fds, pipe_fds, first);
}

//                                           
//    ▓▓▓▓▓▓▒▒▓▓▓▓▒▒▒▒                        
//    ▓▓▓▓▒▒▒▒▒▒▒▒░░▒▒         ██╗░░██╗       
//    ▓▓▒▒▒▒▓▓▒▒▓▓░░▒▒         ╚██╗██╔╝       
//      ▓▓▒▒▓▓██▒▒▒▒           ░╚███╔╝░       
//      ▒▒▒▒▒▒▒▒░░▓▓           ░██╔██╗░       
//      ▒▒▒▒▓▓▓▓░░▒▒           ██╔╝╚██╗       
//      ██▓▓▒▒▒▒░░▓▓           ╚═╝░░╚═╝       
//      ▓▓▓▓▓▓▓▓▒▒▓▓                          
//                                            
