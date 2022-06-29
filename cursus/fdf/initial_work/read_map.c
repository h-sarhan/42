/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/30 01:37:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotX(t_point *p, int x, int y, int z, float rot)
{
	p->x = x;
	p->y = cos(rot) * y - sin(rot) * z;
	p->z = -sin(rot) * y + cos(rot) * z;
}

void	rotY(t_point *p, int x, int y, int z, float rot)
{
	p->x = x * cos(rot) + sin(cos(rot)) * z;
	p->y = y;
	p->z = -sin(rot) * x + cos(rot) * z;
}

void	rotZ(t_point *p, int x, int y, int z, float rot)
{
	p->x = x * cos(rot) - sin(cos(rot)) * y;
	p->y = x * sin(rot) + cos(rot) * y;
	p->z = z;
}

void project_point(t_point *p, int x, int y, int z, int scale, int translate)
{
	float	beta;
	float	alpha;

	beta = 45 * (M_PI / 180.0f);
	alpha = asin(tan(30 * (M_PI / 180.0f)));
	rotZ(p, x * scale, y * scale, z * scale, beta);
	rotX(p, p->x, p->y, p->z, alpha + 25 * (M_PI / 180.0f));
}

t_map	*read_map(char *map_path)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	int		num_rows;
	int		**z_values;
	t_map	*map;
	
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	tokens = ft_split(line, ' ');
	int i = 0;
	while (tokens[i] != NULL)
		i++;
	int num_cols = i;
	lines = NULL;

	num_rows = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		num_rows++;
		line = get_next_line(fd);
	}
	z_values = ft_calloc(num_rows + 1, sizeof(int *));
	i = 0;
	int j = 0;
	while (i < num_rows)
	{
		z_values[i] = ft_calloc(num_cols + 1, sizeof(int));
		j = 0;
		while (j < num_cols)
		{
			line = lines->content;
			tokens = ft_split(line, ' ');
			z_values[i][j] = atoi(tokens[j]);
			j++;
		}
		lines = lines->next;
		i++;
	}
	map = ft_calloc(1, sizeof(t_map));
	map->z_values = z_values;
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	return (map);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	create_points(t_map *map, int scale)
{
	t_point	***points;
	int		i;
	int		j;
	int		min_xval;
	int		min_yval;

	min_xval = 0;
	min_yval = 0;
	i = 0;
	j = 0;
	points = ft_calloc(map->num_rows + 1, sizeof(t_point **));
	while (i < map->num_rows)
	{
		j = 0;
		points[i] = ft_calloc(map->num_cols + 1, sizeof(t_point *));
		while (j < map->num_cols)
		{
			points[i][j] = ft_calloc(1, sizeof(t_point));
			project_point(points[i][j],  i, (map->num_cols - j), map->z_values[i][j], scale, 0);
			if (points[i][j]->x < min_xval)
				min_xval = points[i][j]->x;	
			if (points[i][j]->y < min_yval)
				min_yval = points[i][j]->y;	
			j++;
		}
		i++;
	}
	int xoffset = 0;
	int yoffset = 0;
	if (min_xval < 0)
		xoffset = -min_xval;
	if (min_yval < 0)
		yoffset = -min_yval;
	i = 0;
	j = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			points[i][j]->x += xoffset;
			points[i][j]->y += yoffset;
			j++;
		}
		i++;
	}
	map->points = points;
}

int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	t_map	*map = read_map(argv[1]);
	int scale = 40;
	mlx_win = mlx_new_window(mlx, map->num_cols * scale, map->num_rows * scale, "Hello world!");
	img.img = mlx_new_image(mlx, map->num_cols * scale, map->num_rows * scale);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int i = 0;
	int j = 0;
	create_points(map, 15);
	t_point ***points = map->points;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (j + 1 < map->num_cols)
				draw_line(&img, points[i][j]->x, points[i][j]->y, points[i][j + 1]->x, points[i][j + 1]->y);
			if (i + 1 < map->num_rows)
				draw_line(&img, points[i][j]->x, points[i][j]->y, points[i + 1][j]->x, points[i + 1][j]->y);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
