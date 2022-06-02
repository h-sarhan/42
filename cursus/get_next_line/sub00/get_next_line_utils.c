/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:31:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/02 20:31:49 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*resize(char **arr, int old_len, int new_len)
{
	int		i;
	char	*new_arr;

	i = 0;
	new_arr = malloc(new_len * sizeof(char));
	if (new_arr == NULL)
	{
		free(*arr);
		return (NULL);
	}
	while (i < old_len && i < new_len && (*arr)[i] != '\0')
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	while (i < new_len)
		new_arr[i++] = '\0';
	return (new_arr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
