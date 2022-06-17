/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:50:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/17 06:56:32 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoinfree(char *s1, char *s2, int f)
{
	char	*joined;
	
	if (s1 == NULL || s2 == NULL)
		return (NULL);
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