/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/23 14:42:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>

# define READ 0
# define WRITE 1
# define STDOUT 1
# define STDIN 0
# define BUFFER_SIZE 100

// utils.c
char	*ft_strjoinfree(char *s1, char *s2, int f);
void	free_split_array(char **arr);
void	trim_args(char **args);
char	*get_full_path(char *bin, char **env);
void	check_arg_count(int argc);

// utils2.c
void	ft_free(void *mem);
void	dup_fd(int fd_1, int fd_2);
void	close_fd(int fd);
int		open_file(char *file_path, int outfile);
char	**get_args(char *arg);
// error_handling.c
void	malloc_check(void *mem);
int		command_check(char **cmd_args, char *arg_list, int fd);
void	print_error_string(char *error_str, char *file_name);
void	ft_pipe(int *pipe_fds);
int		ft_fork(int cmd_valid);

// split_args.c
char	**split_args(char const *s, char c);

// Gloabal variable that stores environment variables
extern char					**environ;

// Struct that stores the arguments, process id, validity,
// in_fd, out_fd, and wait status of each command
struct s_command {
	char	**cmd_args;
	int		pid;
	int		valid;
	int		in_fd;
	int		out_fd;
	int		w_status;
};
typedef struct s_command	t_cmd;

// command.c
t_cmd	*create_command(char *cmd_str);
void	wait_cmd(void *cmd);
void	free_cmd(void *cmd);

// run_commands.c
void	run_first_cmd(t_cmd *cmd, int *pipes, int *fds, t_list *cmds);
void	run_middle_cmd(t_cmd *cmd, int *pipes, int *fds, t_list *cmds);
void	run_last_cmd(t_cmd *cmd, int *pipes, int *fds, t_list *cmds);

// pipex.c
t_list	*create_command_list(int argc, char **argv, int *fds, int hd);
void	handle_first_cmd(t_cmd *cmd, int *fds, int *pipes, t_list *cmds);
t_list	*handle_mid_cmds(t_list *cmds, int *pfds, int *fds, t_list *first);
void	wait_and_exit(int *pipe_fds, int *fds, t_list *command_list);
void	handle_last_cmd(t_cmd *cmd, int *fds, int *pipes, t_list *cmds);

// here_doc.c
t_list	*handle_here_doc(int argc, char **argv, int *cmd_pipes, int *fds);

#endif