
#include "fdf.h"

t_map	*read_map(char *map_path, int scale)
{
	int		fd;
	char	*line;
	char	**tokens;
	t_list	*lines;
	t_list	*first;
	int		num_rows;
	t_map	*map;

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
	// free_split_array(tokens);	
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
	t_vector ***points = ft_calloc(num_rows + 1, sizeof(t_vector **));
	while (i < num_rows && lines != NULL)
	{
		points[i] = ft_calloc(num_cols + 1, sizeof(t_vector *));
		line = lines->content;
		tokens = ft_split(line, ' ');
		j = 0;
		while (j < num_cols && tokens[j] != NULL)
		{
			points[i][j] = ft_calloc(1, sizeof(t_vector));
			// if (ft_strchr(tokens[j], ',') != NULL)
			// 	points[i][j]->color = hextoi(ft_strchr(tokens[j], ',') + 1);
			// else
				points[i][j]->color = 0x00FFFFFF;
			
			points[i][j]->x = i;
			points[i][j]->y = num_cols - j;
			points[i][j]->z = atoi(tokens[j]);
			// project_point(points[i][j],  i, num_cols - j, atoi(tokens[j]), scale, 0);
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
		// free_split_array(tokens);
		i++;
	}
	map->proj_points = points;
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	// remap_points(map, 0, scale);
	ft_lstclear(&first, free);
	return (map);
}

void makeBigger(t_map *map, int scale)
{
    int i = 0, j = 0;
    // Image *tmp = (Image*)malloc(sizeof(Image));
    t_map *tmp = ft_calloc(1, sizeof(t_map));
	tmp->max_x = map->max_x * scale;
	tmp->max_y = map->max_y * scale;
	tmp->min_x = map->min_x * scale;
	tmp->min_y = map->min_y * scale;
	tmp->num_cols = map->num_cols * scale;
	tmp->num_rows = map->num_rows * scale;

    tmp->proj_points = ft_calloc(tmp->num_rows + 1, sizeof(t_vector **));
    for (i = 0; i < tmp->num_rows; i++) {
        tmp->proj_points[i] = ft_calloc(tmp->num_cols + 1, sizeof(t_vector *));
        for (j = 0; j < tmp->num_cols; j++) {
			tmp->proj_points[i][j] = ft_calloc(1, sizeof(t_vector));
            tmp->proj_points[i][j]->x = map->proj_points[i / scale][j / scale]->x;
            tmp->proj_points[i][j]->y = map->proj_points[i / scale][j / scale]->y;
            tmp->proj_points[i][j]->z = map->proj_points[i / scale][j / scale]->z;
            tmp->proj_points[i][j]->color = map->proj_points[i / scale][j / scale]->color;
        }
    }
	// free_map(map);
    // for (i = 0; i < map->num_rows; i++)
    //     free(map->points[i]);
    // free(map->points);

    map->num_cols = tmp->num_cols;
    map->num_rows = tmp->num_rows;
    map->proj_points = tmp->proj_points;
    // free(tmp);
}
# include <fcntl.h>
void printPoints(t_map *map)
{
    // printf("Width: %d, Height: %d\n", map->num_cols, map->num_rows);
	int fd = open("amogus_hd.fdf", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    for (int i = 0; i < map->num_rows; i++) {
        for (int j = 0; j < map->num_cols; j++)
		{
            // printf("(%d, %d)", map->points[i][j]->x, map->points[i][j]->y);
            printf("%d", map->proj_points[i][j]->z);
            write(fd, " ", 1);
            ft_putnbr_fd(map->proj_points[i][j]->z, fd);
			if (map->proj_points[i][j]->z == 7 || map->proj_points[i][j]->z == 5)
				ft_putstr_fd(",0xbf1701", fd);
			if (map->proj_points[i][j]->z == 9)
				ft_putstr_fd(",0x97c6db", fd);
            write(fd, " ", 1);
		}
        printf("\n");
        write(fd, "\n", 1);
    }
    printf("\n");
	// write(fd, "\n", 1);
}


int main(int argc, char **argv)
{
	t_map * map = read_map(argv[1], 1);
	makeBigger(map, atoi(argv[2]));
	printPoints(map);
}