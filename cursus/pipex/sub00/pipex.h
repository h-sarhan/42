/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/18 13:46:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// TODO: REMOVE UNECESSARY INCLUDES
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
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
int		fd_check(int fd, char *file_name);
void	pipe_check(int pipe_ret);
void	fork_check(int pid);
void	close_check(int close_ret);
void	dup_fd(int fd_1, int fd_2);
void	close_fd(int fd);
int		command_check(char **cmd_args, char *cmdname, int *exit_code, int fd);



#endif