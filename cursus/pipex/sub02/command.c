/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:27:28 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:14:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Creates and returns a command struct
t_cmd	*create_command(char *cmd_str, char **env)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	malloc_check(cmd);
	cmd->cmd_args = get_args(cmd_str, env);
	cmd->pid = -1;
	cmd->valid = 0;
	cmd->in_fd = -1;
	cmd->out_fd = -1;
	cmd->w_status = 0;
	cmd->env = env;
	return (cmd);
}

// Frees a command
void	free_cmd(void *cmd)
{
	t_cmd	*command;

	command = cmd;
	free_split_array(command->cmd_args);
	free(command);
}

// Waits for a command's child process
void	wait_cmd(void *cmd)
{
	t_cmd	*command;

	command = cmd;
	waitpid(command->pid, &command->w_status, 0);
}
