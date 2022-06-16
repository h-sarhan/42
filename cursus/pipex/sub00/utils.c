/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 10:50:21 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/16 11:13:08 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoinfree(char *s1, char *s2, int f)
{
	char	*joined;
	
	joined = ft_strjoin(s1, s2);
	if (f == 1)
		free(s1);
	if (f == 2)
		free(s2);
	if (f == 3)
	{
		free(s1);
		free(s2);
	}
	return (joined);
}

void	free_split_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}