/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_og.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/04 18:31:26 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotX(t_point *p, float x, float y, float z, float rot)
{
	p->x = x;
	p->y = cos(rot) * y - sin(rot) * z;
	p->z = -sin(rot) * y + cos(rot) * z;
}

void rotY(t_point *p, float x, float y, float z, float rot)
{
	p->x = x * cos(rot) + sin(cos(rot)) * z;
	p->y = y;
	p->z = -sin(rot) * x + cos(rot) * z;
}

void rotZ(t_point *p, float x, float y, float z, float rot)
{
	p->x = x * cos(rot) - sin(cos(rot)) * y;
	p->y = x * sin(rot) + cos(rot) * y;
	p->z = z;
}

void project_point(t_point *p, int x, int y, int z, int scale, int translate)
{
	float beta;
	float alpha;

	beta = 45 * (PI / 180.0f);
	alpha = asin(tan(30 * (PI / 180.0f)));
	p->x = x * scale;
	p->y = y * scale;
	p->z = z * scale;
	rotZ(p, p->x, p->y, p->z, beta);
	rotX(p, p->x, p->y, p->z, alpha + 30 * (PI / 180.0f));
}

void free_split_array(char **arr)
{
	int i;

	if (arr == NULL)
		return;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_lines(void *split_array)
{
	free_split_array(split_array);
}

t_map *read_map(char *map_path, int scale)
{
	int fd;
	char *line;
	char **tokens;
	t_list *lines;
	t_list *first;
	int num_rows;
	t_map *map;

	map = ft_calloc(1, sizeof(t_map));
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	tokens = ft_split(line, ' ');
	int i = 0;
	while (tokens[i] != NULL)
		i++;
	int num_cols = i;
	free_split_array(tokens);
	lines = NULL;
	num_rows = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		num_rows++;
		line = get_next_line(fd);
	}
	first = lines;
	i = 0;
	int j = 0;
	t_point ***points = ft_calloc(num_rows + 1, sizeof(t_point **));
	while (i < num_rows && lines != NULL)
	{
		points[i] = ft_calloc(num_cols + 1, sizeof(t_point *));
		line = lines->content;
		tokens = ft_split(line, ' ');
		j = 0;
		while (j < num_cols && tokens[j] != NULL)
		{
			points[i][j] = ft_calloc(1, sizeof(t_point));
			if (ft_strchr(tokens[j], ',') != NULL)
				points[i][j]->color = hextoi(ft_strchr(tokens[j], ',') + 1);
			else
				points[i][j]->color = 0x00FFFFFF;

			project_point(points[i][j], i, num_cols - j, atoi(tokens[j]), scale, 0);
			if (points[i][j]->x < map->min_x)
				map->min_x = points[i][j]->x;
			if (points[i][j]->y < map->min_y)
				map->min_y = points[i][j]->y;
			if (points[i][j]->x > map->max_x)
				map->max_x = points[i][j]->x;
			if (points[i][j]->y > map->max_y)
				map->max_y = points[i][j]->y;
			j++;
		}
		lines = lines->next;
		free_split_array(tokens);
		i++;
	}
	map->projected_points = points;
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	remap_points(map, 0, scale);
	ft_lstclear(&first, free);
	return (map);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void remap_points(t_map *map, int translate, int scale)
{
	int i = 0;
	int j = 0;

	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->min_x < 0)
				map->projected_points[i][j]->x -= map->min_x;
			if (map->min_y < 0)
				map->projected_points[i][j]->y -= map->min_y;
			j++;
		}
		i++;
	}
	if (map->min_x < 0)
	{
		map->max_x -= map->min_x;
		map->min_x = 0;
	}
	if (map->min_y < 0)
	{
		map->max_y -= map->min_y;
		map->min_y = 0;
	}
}

void free_map(t_map *map)
{
	int i = 0;
	i = 0;
	int j = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			free(map->projected_points[i][j]);
			j++;
		}
		free(map->projected_points[i]);
		i++;
	}
	free(map->projected_points);
	free(map);
}

#include <time.h>
int main(int argc, char **argv)
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	clock_t t;
	t = clock();
	int scale = atoi(argv[2]);
	t_map *map = read_map(argv[1], scale);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("read_map() took %f seconds to execute \n", time_taken);

	int i = 0;
	int j = 0;

	int translate = 20;
	mlx_win = mlx_new_window(mlx, map->max_x + translate + 1, map->max_y + translate + 1, "fdf");
	img.img = mlx_new_image(mlx, map->max_x + translate + 1, map->max_y + translate + 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	t = clock();
	t_point ***points = map->projected_points;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (j + 1 < map->num_cols)
				draw_line(&img, translate + points[i][j]->x, translate + points[i][j]->y, translate + points[i][j + 1]->x, translate + points[i][j + 1]->y, points[i][j]->color);
			if (i + 1 < map->num_rows)
				draw_line(&img, translate + points[i][j]->x, translate + points[i][j]->y, translate + points[i + 1][j]->x, translate + points[i + 1][j]->y, points[i][j]->color);
			j++;
		}
		i++;
	}
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
	printf("draw_points() took %f seconds to execute \n", time_taken);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_map(map);
}
