/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:28:28 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/03 11:29:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define STDOUT 1
# define TRUE 1
# define FALSE 0

char	*get_next_line(int fd);
void	*resize(char **arr, int old_len, int new_len);
char	*extract_line(int fd, char **line_buffer);
int		ft_strlen(char *str);
int		max(int a, int b);

#endif