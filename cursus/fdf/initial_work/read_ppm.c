/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:00:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/07 15:38:34 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
void	edge_detect(t_map *map);
t_map *read_map_from_ppm(char *map_path)
{
	int		fd;
	char	**tokens;
	t_map	*map;
	int scale = 1;
	// TODO: Write create map function
	map = ft_calloc(1, sizeof(t_map));
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;

	fd = open(map_path, O_RDONLY);
	// int i = 0;
	int w, h;
	char *header = get_next_line(fd);
	if (ft_strncmp(header, "P6\n", ft_strlen(header)) != 0)
	{
		ft_printf("CANT READ THIS LOOL\n");
	}
	header = get_next_line(fd);
	tokens = ft_split(header, ' ');
	w = ft_atoi(tokens[0]);
	h = ft_atoi(tokens[1]);
	
	while (w * scale < 400 && h * scale < 400)
		scale++;
	header = get_next_line(fd);
	// header = get_next_line(fd);
	t_point ***points = ft_calloc(h + 1, sizeof(t_point **));
	t_point ***points_copy = ft_calloc(h + 1, sizeof(t_point **));
	t_point ***projected_points = ft_calloc(h + 1, sizeof(t_point **));
	for (int i = 0; i < h; i++)
	{
		points[i] = ft_calloc(w + 1, sizeof(t_point *));
		points_copy[i] = ft_calloc(w + 1, sizeof(t_point *));
		projected_points[i] = ft_calloc(w + 1, sizeof(t_point *));
		for (int j = 0; j < w; j++)
		{
			projected_points[i][j] = ft_calloc(1, sizeof(t_point));
			points[i][j] = ft_calloc(1, sizeof(t_point));
			points_copy[i][j] = ft_calloc(1, sizeof(t_point));
			int r, g, b;
			r = 0;
			g = 0;
			b = 0;
			read(fd, &g, 1);
			read(fd, &b, 1);
			read(fd, &r, 1);
			projected_points[i][j]->color = create_trgb(0, r, g, b);
			points[i][j]->x = i;
			points[i][j]->y = (h - j) * scale;
			points[i][j]->z = 0;
			points_copy[i][j]->x = i * scale;
			points_copy[i][j]->y = (h - j) * scale;
			points_copy[i][j]->z = 0;
		}
	}
	map->projected_points = projected_points;
	map->points = points;
	map->points_copy = points_copy;
	map->num_cols = w;
	map->num_rows = h;
	// edge_detect(map);
	find_min_max(map, map->points_copy);
	project_points(map, scale, 'i');
	// remap_points(map, 0, 0);
	// ft_lstclear(&first, free);
	return (map);
}

// int get_gray(int color)
// {
// 	int r = get_r(color);
// 	int g = get_g(color);
// 	int b = get_b(color);
// 	int gray = (r + g + b) / 3;
// 	return (gray);
// }

// void	edge_detect(t_map *map)
// {
// 	t_point ***points = map->projected_points;
// 	int		**colors = ft_calloc(map->num_rows + 2, sizeof(int *));
// 	for (int i = 1; i < map->num_rows - 1; i++)
// 	{
// 		colors[i] = ft_calloc(map->num_cols + 2, sizeof(int));
// 		for (int j = 1; j < map->num_cols - 1; j++)
// 		{
// 			int sum = 0;
// 			sum += get_gray(points[i-1][j-1]->color);
// 			sum += get_gray(points[i-1][j]->color) * 2;
// 			sum += get_gray(points[i-1][j + 1]->color);
// 			sum += get_gray(points[i][j-1]->color) * 2;
// 			sum += get_gray(points[i][j]->color) * 4;
// 			sum += get_gray(points[i][j+1]->color) * 2;
// 			sum += get_gray(points[i + 1][j- 1]->color);
// 			sum += get_gray(points[i + 1][j]->color) * 2;
// 			sum += get_gray(points[i + 1][j+1]->color);
// 			sum /= 16;
// 			if (sum > 255)
// 				sum = 255;
// 			if (sum < 0)
// 				sum = 0;
// 			colors[i][j] = sum;
// 			// printf("POINT (%d, %d)", );
// 		}
// 	}
// 	int		**colors2 = ft_calloc(map->num_rows + 2, sizeof(int *));
// 	for (int i = 2; i < map->num_rows - 2; i++)
// 	{
// 		colors2[i] = ft_calloc(map->num_cols + 2, sizeof(int));
// 		for (int j = 2; j < map->num_cols - 2; j++)
// 		{
// 			int sum = 0;
// 			sum += colors[i - 1][j - 1] * -1;
// 			sum += colors[i - 1][j]     *  0;
// 			sum += colors[i - 1][j + 1] *  1;
// 			sum += colors[i][j - 1]     * -1;
// 			sum += colors[i][j]         *  0;
// 			sum += colors[i][j + 1]     *  1;
// 			sum += colors[i + 1][j - 1] * -1;
// 			sum += colors[i + 1][j]     *  0;
// 			sum += colors[i + 1][j + 1] *  1;
// 			if (sum < 25)
// 				sum = 0;
// 			if (sum > 0)
// 				sum = 255;
// 			colors2[i][j] = sum;
// 			// printf("POINT (%d, %d)", );
// 		}
// 	}
	// for (int i = 2; i < map->num_rows - 2; i++)
	// {
	// 	int start = 2;
	// 	int end = map->num_cols - 3;
	// 	int alt = 50;
	// 	float thickness1 = 0;
	// 	float thickness2 = 0;
	// 	while (start < end)
	// 	{
	// 		while (colors2[i][start] == 0 && start < end)
	// 			start++;
	// 		float val1 = colors2[i][start] / 255.0f;
	// 		while (colors2[i][start] != 0 && start < end)
	// 		{
	// 			start++;
	// 			thickness1++;
	// 		}
	// 		// val1 *= thickness1 / 2;
	// 		while (colors2[i][end] == 0 && start < end)
	// 			end--;
	// 		float val2 = colors2[i][end] / 255.0f;
	// 		while (colors2[i][end] != 0 && start < end)
	// 		{
	// 			end--;
	// 			thickness2++;
	// 		}
	// 		// val2 *= thickness2 / 2;
	// 		while (colors2[i][start] == 0 && start < end)
	// 			map->points[i][start++]->z = alt * val1;
	// 		while (colors2[i][end] == 0 && start < end)
	// 			map->points[i][end--]->z = alt * val2;
	// 		// alt += 5;
	// 	}
	// }
	// for (int i = 2; i < map->num_rows - 2; i++)
	// 	for (int j = 2; j < map->num_cols - 2; j++)
	// 	{
	// 		int gray =  create_trgb(0, colors2[i][j], colors2[i][j], colors2[i][j]);
	// 		map->projected_points[i][j]->color = gray;
	// 	}
// }