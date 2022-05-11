/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:15:57 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/11 20:55:23 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>

# include "c_unit/c_unit.h"
# include "../libft.h"

// Libc tests

// ASCII tests
void	test_isalpha();
void	test_isdigit();
void	test_isalnum();
void	test_isascii();
void	test_isprint();

// String tests
void	test_strlen();
void	test_toupper();
void	test_tolower();
void	test_strchr();
void	test_strrchr();
void	test_strdup();
void	test_strncmp();

// Memory tests
void	test_memset();
void	test_memchr();
void	test_bzero();
void	test_memcpy();
void	test_calloc();
void	test_memchr();

// Additional function tests
void	test_ft_substr();
void	test_ft_putchar_fd();
void	test_ft_putstr_fd();
void	test_ft_putendl_fd();
void	test_ft_putnbr_fd();
#endif
