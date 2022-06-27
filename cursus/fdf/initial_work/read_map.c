/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/27 18:36:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

struct s_point {
	int	x;
	int	y;
};

typedef struct s_point	t_point;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	project_point(t_point *p, int x, int y, int z)
{
	// int	cf1_x;
	// int	cf1_z;

	// cf1_x = CF1 * x;
	// cf1_z = CF1 * z;
	// p->x = CF2 * cf1_x - CF2 * cf1_z;
	// p->y = cf1_x + CF3 * y + cf1_z;
	// p->x = sq
}

t_point	**read_map(char *map_path)
{
	int		fd;
	char	*line;

	// RETURN A 2D ARRAY OF POINTS
	// Read a line from the map
	// Generate x, y, z values from each token on the line
	// x will be the word idx
	// y will be the line_idx
	// z will be the atoi'd value of the token
	// project x and y
	// point->p_x = projected x
	// point->p_y = projected y
	// will have to malloc the 2D points array
	// will have to free each line
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
	t_point p1;
	t_point p2;
	project_point(&p1, 500, 500, 0);
	project_point(&p2, 500, 500, 200);
	printf("p1.x == %d\n", p1.x);
	printf("p1.y == %d\n", p1.y);
	printf("p2.x == %d\n", p2.x);
	printf("p2.y == %d\n", p2.y);
	if (p1.x > p2.x)
		draw_line(&img, p2.x, p2.y, p1.x, p1.y);
	else
		draw_line(&img, p1.x, p1.y, p2.x, p2.y);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

// int main(int argc, char **argv)
// {
// 	if (argc >= 2)
// 		read_map(argv[1]);

// 	return (0);
// }