/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:35:32 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/30 00:52:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"

# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define SCREEN_W 1280
# define SCREEN_H 720
# define CF1 0.40824829046F // sqrt(6)/6
# define CF2 1.73205080757F // sqrt(3)
# define CF3 0.81649658092F // 2 * sqrt(6)/6

struct s_point
{
	int x;
	int y;
	int	z;
};

typedef struct s_point t_point;

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

struct s_map
{
	int		**z_values;
	int		num_rows;
	int		num_cols;
	t_point	***points;
};
typedef struct s_map	t_map;


void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_line(t_data *img, int x0, int y0, int x1, int y1);

// void	read_map(char *map_path);


#endif