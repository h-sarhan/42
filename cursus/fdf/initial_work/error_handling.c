/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:40:23 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 16:58:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_msg(char *msg, int code)
{
	ft_printf(msg);
	exit(code);
}

void	exit_free(void *p1, void *p2, void *p3)
{
	ft_printf("ERROR READING MAP");
	if (p1 != NULL)
		free(p1);
	if (p2 != NULL)
		free(p2);
	if (p3 != NULL)
		free(p3);
	exit(EXIT_FAILURE);
}

void	free_split_array(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
