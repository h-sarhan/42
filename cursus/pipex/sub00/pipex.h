/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/17 07:22:23 by hsarhan          ###   ########.fr       */
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
char	*ft_strjoinfree(char *s1, char *s2, int f);
void	free_split_array(char **arr);
void	ft_free(void *mem);


#endif