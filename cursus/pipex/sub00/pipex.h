/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/21 10:56:06 by hsarhan          ###   ########.fr       */
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
# include <sys/errno.h>
# include "printf/ft_printf.h"
# include "libft/libft.h"

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
void	run_command(int *pipe_fds, int *fds, char **cmd_args, char **env);

// error_handling.c
void	malloc_check(void *mem);
int		command_check(char **cmd_args, char *arg_list, int fd);
void	print_error_string(char *error_str, char *file_name);
void	ft_pipe(int *pipe_fds);
int		ft_fork(int cmd_valid);

// split_args.c
char	**split_args(char const *s, char c);

#endif