/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:39:42 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/24 21:26:46 by hsarhan          ###   ########.fr       */
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

typedef int	bool;
struct	s_conversion {
	char	type;
	int		min_width;
	bool	pad_zeros;
	bool	precision;
	int		precision_amount;
	bool	alt_form;
	bool	space;
	bool	sign;
	bool	pad_right;
	int		mw_padding;
	int		pr_padding;
};
typedef struct s_conversion	t_conversion;
void			print_unsigned_int(unsigned int num);
int				print_hex_pointer(void *pointer);
int				print_hex_int(unsigned int num, char hex_type);
int				print_hex(unsigned long num, char hex_type);
int				count_args(const char *fmt);
int				count_digits_int(int num);
int				count_digits_unsigned(unsigned int num);
int				ft_printf(const char *fmt, ...);
void			parse_conversion_string(char *fmt, t_conversion *conv);
int				count_hex(unsigned long num);
t_conversion	*new_conversion(char *fmt);
int				print_conversion(t_conversion *conv, void *val);
void			print_n_chars(char c, int n);
#endif
