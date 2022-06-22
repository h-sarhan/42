/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/22 06:48:13 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../printf/ft_printf.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/errno.h>

# define READ 0
# define WRITE 1
# define STDOUT 1
# define STDIN 0

// utils.c
char	*ft_strjoinfree(char *s1, char *s2, int f);
void	free_split_array(char **arr);
void	trim_args(char **args);
void	check_arg_count(int argc);
char	*get_full_path(char *bin, char **env);

// utils2.c
void	ft_free(void *mem);
void	dup_fd(int fd_1, int fd_2);
void	close_fd(int fd);
int		open_file(char *file_path, int outfile);
char	**get_args(char *arg, char **env);

// error_handling.c
void	malloc_check(void *mem);
int		command_check(char **cmd_args, char *arg_list, int fd);
void	print_error_string(char *error_str, char *file_name);
void	ft_pipe(int *pipe_fds);
int		ft_fork(int cmd_valid);

// split_args.c
char	**split_args(char const *s, char c);

struct s_command {
	char	**cmd_args;
	int		pid;
	int		valid;
};

typedef struct s_command t_command;

// command.c
t_command	*create_command(char *cmd_str, char **env);
void		run_first_cmd(t_command *cmd, int *pipe_fds, int *fds, char **env);
void		run_middle_cmd(t_command *cmd, int *pipe_fds, int *fds, char **env);
void		run_last_cmd(t_command *cmd, int *pipe_fds, int *fds, char **env);
void		free_cmd(void *cmd);

#endif