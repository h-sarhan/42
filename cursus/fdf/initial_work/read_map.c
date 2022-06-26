/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/26 17:12:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(int argc, char **argv)
{
	if (argc >= 2)
	{
		int fd = open(argv[1], O_RDONLY);
		char *line = get_next_line(fd);
		while (line != NULL)
		{
			ft_printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
	}
}
