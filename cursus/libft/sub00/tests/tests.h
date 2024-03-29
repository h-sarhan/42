/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:15:57 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/14 19:33:16 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <ctype.h>
# include <stdlib.h>
# include <string.h>
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
void	test_atoi();
void	test_strlcpy();
void	test_strlcat();

// Memory tests
void	test_memset();
void	test_memchr();
void	test_bzero();
void	test_memcpy();
void	test_calloc();
void	test_memchr();
void	test_memcmp();
void	test_memmove();
void	test_strnstr();

// Additional function tests
void	test_ft_substr();
void	test_ft_strtrim();
void	test_ft_split();
void	test_ft_itoa();
void	test_ft_strmapi();
void	test_ft_striteri();
void	test_ft_strjoin();

// Put tests
void	test_ft_putchar_fd(int flag);
void	test_ft_putstr_fd(int flag);
void	test_ft_putendl_fd(int flag);
void	test_ft_putnbr_fd(int flag);

// Bonus test
void	test_ft_lstnew();
void	test_ft_lstadd_front();
void	test_ft_lstsize();
void	test_ft_lstlast();
void	test_ft_lstadd_back();
void	test_ft_lstdelone();
void	test_ft_lstclear();
void	test_ft_lstiter();
void	test_ft_lstmap();
#endif
