/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:35:32 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/01 20:13:15 by hsarhan          ###   ########.fr       */
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
# define ON_DESTROY 17
# define KEY_Q 12
# define KEY_ESC 53

struct s_point
{
	int				x;
	int				y;
	int				z;
	int	color;
};

typedef struct s_point t_point;

struct	s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
};
typedef struct s_data	t_data;

struct s_map
{
	int				num_rows;
	int				num_cols;
	t_point			***projected_points;
	t_point			***points;
	int				min_xval;
	int				max_xval;
	int				min_yval;
	int				max_yval;
};
typedef struct s_map	t_map;

struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*img;
};

typedef struct s_vars t_vars;


void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	hextoi(char *str);
void			draw_line(t_data *img, t_point *p1, t_point *p2);
void			remap_points(t_map *map, int translate, int scale);
int				create_trgb(unsigned int t, unsigned int r, unsigned int g, unsigned int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				add_color(int color1, int color2);
int				color_mix(int c1, int c2, float mix);

#endif