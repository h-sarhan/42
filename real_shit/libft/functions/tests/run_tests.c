/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:15:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/11 19:19:58 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#define MAGENTA "\x1b[35m"

int	main()
{
	srand(42);
	print_msg_color("\n===Testing libc ascii functions===\n", MAGENTA);
//	test_isalpha();
//	test_isdigit();
//	test_isalnum();
//	test_isascii();
//	test_isprint();
//
//	print_msg_color("\n===Testing libc string functions===\n", MAGENTA);
//	test_strlen();
//	test_toupper();
//	test_tolower();
//	test_strchr();
//	test_strrchr();
//	test_strdup();
//	test_strncmp();
//  
//  	print_msg_color("\n===Testing libc memory functions===\n", MAGENTA);
//	test_memset();
//	test_bzero();
//	test_memcpy();
//	test_calloc();
//	test_memchr();
//
	print_msg_color("\n===Testing additional functions===\n", MAGENTA);
	test_ft_putchar_fd();
}
