/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:15:57 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/10 15:19:44 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

# include "c_unit/c_unit.h"
# include "libft.h"

void	test_isalpha();
void	test_isdigit();
void	test_isalnum();
void	test_isascii();
void	test_isprint();
void	test_strlen();
void	test_memset();
void	test_bzero();
void	test_memcpy();
void	test_toupper();
void	test_tolower();
void	test_strchr();
void	test_strrchr();
void	test_calloc();

#endif
