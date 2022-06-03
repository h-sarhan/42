/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:42:40 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/03 12:52:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# define STDOUT 1
# define TRUE 1
# define FALSE 0

// get_next_line.c
char	*get_next_line(int fd);
char	*extract_line(int fd, char **line_buffer);
int		go_to_next_line(int fd, char **line_buffer);
int		read_into_buffer(char **buffer, int fd, int chars_read, int *max_size);
char	*create_line(char **line_buffer, int line_length);

// get_next_line_utils.c
int		ft_strlen(char *str);
void	*resize(char **arr, int old_len, int new_len);
int		max(int a, int b);

#endif