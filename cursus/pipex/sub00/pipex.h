/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/21 09:59:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <sys/errno.h>
# include "printf/ft_printf.h"
# include "libft/libft.h"

# define READ 0
# define WRITE 1
# define STDOUT 1
# define STDIN 0

char	*ft_strjoinfree(char *s1, char *s2, int f);
void	free_split_array(char **arr);
void	ft_free(void *mem);
void	malloc_check(void *mem);
void	pipe_check(int pipe_ret);
void	close_check(int close_ret);
void	dup_fd(int fd_1, int fd_2);
void	close_fd(int fd);
int		command_check(char **cmd_args, char *arg_list, int fd);
int		open_file(char *file_path, int outfile);
void	trim_args(char **args);
char	**split_args(char const *s, char c);
void	print_error_string(char *error_str, char *file_name);
void	ft_pipe(int *pipe_fds);
int		ft_fork(int cmd_valid);
void	check_arg_count(int argc);
void	wait_and_exit(int *pids, int out_fd, int cmd_2_valid);
void	run_command(int *pipe_fds, int *fds, char **cmd_args, char **env);
char	*get_full_path(char *bin, char **env);



#endif