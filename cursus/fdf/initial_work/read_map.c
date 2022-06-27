/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/27 17:05:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(char *map_path)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("\n");
}

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *img, int x1, int y1, int x2, int y2)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;

	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 * dx - dy;
	while (x < x2)
	{
		my_mlx_pixel_put(img, x, y, 0x00FF0000);
		x++;
		if (p < 0)
			p += 2 * dy;
		else
		{
			p += 2 * dy - 2 * dx;
			y++;
		}
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 1280, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
	draw_line(&img, 10, 12, 50, 17);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

// int main(int argc, char **argv)
// {
// 	if (argc >= 2)
// 		read_map(argv[1]);

// 	return (0);
// }