/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:15:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/15 14:33:02 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"
#define MAGENTA "\x1b[35m"

int	main(int argc, char **argv)
{
	srand(41);
	
	if (argc != 1 && strcmp(argv[1], "putchar") == 0)
		test_ft_putchar_fd(atoi(argv[2]));
	else if (argc != 1 && strcmp(argv[1], "putstr") == 0)
		test_ft_putstr_fd(atoi(argv[2]));
	else if (argc != 1 && strcmp(argv[1], "putendl") == 0)
		test_ft_putendl_fd(atoi(argv[2]));
	else if (argc != 1 && strcmp(argv[1], "putnbr") == 0)
		test_ft_putnbr_fd(atoi(argv[2]));
	else
	{
		print_msg_color("\n===Testing libc ascii functions===\n", MAGENTA);
		test_isalpha();
		test_isdigit();
		test_isalnum();
		test_isascii();
		test_isprint();
	
		print_msg_color("\n===Testing libc string functions===\n", MAGENTA);
		test_strlen();
		test_toupper();
		test_tolower();
		test_strchr();
		test_strrchr();
		test_strdup();
		test_strncmp();
		test_strnstr();
	  	test_atoi();
	  	test_strlcpy(); // <---- TEST HARDER (DONE)
		test_strlcat(); // <---- TEST HARDER (DONE)
	
		print_msg_color("\n===Testing libc memory functions===\n", MAGENTA);
		test_memset();
		test_bzero();
  		test_calloc();
		test_memchr();
		test_memcmp();
		test_memcpy(); 
		test_memmove(); // <---- TEST HARDER (DONE)
	
		print_msg_color("\n===Testing additional functions===\n", MAGENTA);
		test_ft_substr(); // <--- TEST HARDER (DONE)
		test_ft_strjoin(); // <--- TEST HARDER (DONE)
		test_ft_strtrim();
  		test_ft_split();
		test_ft_itoa();
		test_ft_strmapi();
		test_ft_striteri();
	  
		print_msg_color("\n===Testing bonus functions===\n", MAGENTA);
		test_ft_lstnew();
		test_ft_lstadd_front();
		test_ft_lstsize();
		test_ft_lstlast();
		test_ft_lstadd_back();
		test_ft_lstdelone(); // <--- TEST HARDER (DONE)
		test_ft_lstclear(); // <--- TEST HARDER (DONE)
		test_ft_lstiter();
	    test_ft_lstmap(); // <--- TEST HARDER (DONE)
	}
}
