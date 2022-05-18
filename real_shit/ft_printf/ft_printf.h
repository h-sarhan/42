/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:39:42 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/18 17:29:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdio.h>

# define STDOUT 1
# define TRUE 1
# define FALSE 0
# define UPPER 1
# define LOWER 0

void	print_unsigned_int(unsigned int num);
void	print_hex_pointer(void *pointer);
void	print_hex_int(unsigned int num, int print_upper);
void	print_hex(unsigned long num, int print_upper);
#endif
