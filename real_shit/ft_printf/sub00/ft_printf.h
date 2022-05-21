/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:39:42 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/21 05:53:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdarg.h>

# define STDOUT 1
# define TRUE 1
# define FALSE 0
# define UPPER 1
# define LOWER 0

struct	s_conversion {
	char	type;
	int		min_width;
	int		pad_zeros;
	int		precision;
	int		precision_amount;
	int		alt_form;
	int		space;
	int		sign;
	int		pad_right;
};
typedef struct s_conversion	t_conversion;
void			print_unsigned_int(unsigned int num);
int				print_hex_pointer(void *pointer);
int				print_hex_int(unsigned int num, int print_upper);
int				print_hex(unsigned long num, int print_upper);
int				count_args(const char *fmt);
int				count_digits_int(int num);
int				count_digits_unsigned(unsigned int num);
int				ft_printf(const char *fmt, ...);
void			parse_conversion_string(char *fmt, t_conversion *conv);
t_conversion	*new_conversion(char *fmt);
int				print_conversion(t_conversion *conv, void *val);
#endif
