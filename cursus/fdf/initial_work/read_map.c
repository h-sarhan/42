/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/26 21:44:36 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(char *map_path)
{
	int fd = open(map_path, O_RDONLY);
	char *line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("\n");
}

int main(int argc, char **argv)
{
	if (argc >= 2)
		read_map(argv[1]);
	return (0);
}