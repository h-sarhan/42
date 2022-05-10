/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:15:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/10 15:35:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#define MAGENTA "\x1b[35m"

int	main()
{
	srand(42);
	print_msg_color("\n===Testing ascii functions===\n", MAGENTA);
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();

	print_msg_color("\n===Testing string functions===\n", MAGENTA);
	test_strlen();
	test_toupper();
	test_tolower();
	test_strchr();
	test_strrchr();
	
	print_msg_color("\n===Testing memory functions===\n", MAGENTA);
	test_memset();
	test_bzero();
	test_memcpy();
}
