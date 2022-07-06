/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:35:32 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/06 21:05:50 by hsarhan          ###   ########.fr       */
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
# define PI           3.14159265358979323846F

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
	t_point			***points;
	t_point			***points_copy;
	t_point			***projected_points;
	int				rot_x;
	int				rot_y;
	int				rot_z;
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
	int				max_og_x;
	int				max_og_y;
	int				max_og_z;
};
typedef struct s_map	t_map;



struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*img;
	t_data	*data;
	int		scale;
	int		win_x;
	int		win_y;
	int		translateX;
	int		translateY;
	int		drawing_frame;
	int	m_prev_x;
	int	m_prev_y;
	int	m_x;
	int	m_y;
	int	m_down;
};
typedef struct s_vars t_vars;


void			my_mlx_pixel_put(t_data *data, int x, int y, int color, t_vars *vars);
unsigned int	hextoi(char *str);
void			draw_line(t_data *img, t_point *p1, t_point *p2, t_vars *vars);
void			remap_points(t_map *map, int translate, int scale);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				add_color(int color1, int color2);
int				color_mix2(int color, int step, float t_diff, float r_diff, float g_diff, float b_diff);
int				color_mix(int c1, int c2, float mix);
void			draw_points(t_vars *vars);
void			find_min_max(t_map *map, t_point ***points);
#endif