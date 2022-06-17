/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:50:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/17 18:20:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoinfree(char *s1, char *s2, int f)
{
	char	*joined;
	
	joined = ft_strjoin(s1, s2);
	if (f == 1)
		ft_free(s1);
	if (f == 2)
		ft_free(s2);
	if (f == 3)
	{
		ft_free(s1);
		ft_free(s2);
	}
	return (joined);
}

void	free_split_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		ft_free(arr[i]);
		i++;
	}
	ft_free(arr);
}

void	ft_free(void *mem)
{
	if (mem != NULL)
		free(mem);
}

void	dup_fd(int fd_1, int fd_2)
{
	int	dup_ret;

	if (fd_1 != -1)
	{
		dup_ret = dup2(fd_1, fd_2);
		if (dup_ret == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_fd(int fd)
{
	int	close_ret;

	close_ret = close(fd);
	if (close_ret == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}