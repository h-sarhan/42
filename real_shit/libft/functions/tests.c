/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:12:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/10 00:14:24 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "c_unit/c_unit.h"
#include "libft.h"

void	test_isalpha()
{
	print_msg_color("\n---Testing ft_isalpha---\n", BLUE);
	bool	test = true;
	bool	ft_res;
	bool	libc_res;
	int i =  0;
	while (i < 128)
	{
		ft_res = ft_isalpha(i);
		libc_res = isalpha(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing all possible ascii values: ", test);

	i = 128;
	while (i < 256)
	{
		ft_res = ft_isalpha(i);
		libc_res = isalpha(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing impossible ascii values: ", test);
}

void	test_isdigit()
{
	print_msg_color("\n---Testing ft_isdigit---\n", BLUE);
	bool	test = true;
	bool	ft_res;
	bool	libc_res;
	int	i = 0;
	while (i < 128)
	{
		ft_res = ft_isdigit(i);
		libc_res = isdigit(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing all possible ascii values: ", test);

	i = 128;
	while (i < 256)
	{
		ft_res = ft_isdigit(i);
		libc_res = isdigit(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing impossible ascii values: ", test);
}

void	test_isalnum()
{
	print_msg_color("\n---Testing ft_isalnum---\n", BLUE);
	bool	test = true;
	bool	ft_res;
	bool	libc_res;
	int	i = 0;
	while (i < 128)
	{
		ft_res = ft_isalnum(i);
		libc_res = isalnum(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing all possible ascii values: ", test);

	i = 128;
	while (i < 256)
	{
		ft_res = ft_isalnum(i);
		libc_res = isalnum(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing impossible ascii values: ", test);
}

void	test_isascii()
{
	print_msg_color("\n---Testing ft_isascii---\n", BLUE);
	bool	test = true;
	bool	ft_res;
	bool	libc_res;
	int	i = 0;
	while (i < 128)
	{
		ft_res = ft_isascii(i);
		libc_res = isascii(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing all possible ascii values: ", test);

	i = 128;
	while (i < 256)
	{
		ft_res = ft_isascii(i);
		libc_res = isascii(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing impossible ascii values: ", test);
}

void	test_isprint()
{
	print_msg_color("\n---Testing ft_isprint---\n", BLUE);
	bool	test = true;
	bool	ft_res;
	bool	libc_res;
	int	i = 0;
	while (i < 128)
	{
		ft_res = ft_isprint(i);
		libc_res = isprint(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing all possible ascii values: ", test);

	i = 128;
	while (i < 256)
	{
		ft_res = ft_isprint(i);
		libc_res = isprint(i);
		if (!assert_true("", ft_res == libc_res))
			test = false;
		i++;
	}
	assert_true("Testing impossible ascii values: ", test);
}

void	test_strlen()
{
	print_msg_color("\n---Testing ft_strlen---\n", BLUE);

	char	str[100001];

	int 	test_num = 0;
	bool	test = true;
	print_msg_color("Testing with random strings (<= 100000 chars)\n", YELLOW);
	while (test_num < 1000)
	{
		int	str_len = rand() % 100001;
		int	j = 0;
		while (j < str_len)
		{
			str[j] = 1 + (rand() % 127);
			j++;
		}
		str[j] = '\0';
		if(!assert_true("", ft_strlen(str) == strlen(str)))
			test = false;
		test_num++;
	}
	assert_true("Passed 1000 randomised tests: ", test);
}

void	test_memset()
{
	print_msg_color("\n---Testing ft_memset---\n", BLUE);
	int	memsize = 1000;
	char	*result = malloc(memsize);
	char	*expected = malloc(memsize);
	result = memset(result, 1, memsize);
	expected = memset(expected, 1, memsize);

	result = ft_memset(result, 12, 123);
	expected = memset(expected, 12, 123);
	int 	i = 0;
	bool	test = true;
	while (i < memsize)
	{
		if(!assert_true("", result[i] == expected[i]))
			test = false;
		i++;
	}
	assert_true("Wrote 12 to 123 bytes: ", test);
	free(result);
	free(expected);
	
	char	expected_byte;
	char	*expected_byte_ptr = &expected_byte;
	char	result_byte;
	char	*result_byte_ptr = &result_byte;
	test = true;
	i = 0;
	while (i < 256)
	{
		result_byte_ptr = ft_memset(result_byte_ptr, i, 1);
		expected_byte_ptr = memset(expected_byte_ptr, i, 1);
		if (!assert_true("", *result_byte_ptr == *expected_byte_ptr))
			test = false;
		i++;
	}
	assert_true("Writing all possible single byte values: ", test);
	

	int num_tests = 1000;
	i = 0;
	test = true;
	print_msg_color("Starting random ft_memset tests: \n", YELLOW);
	while (i < num_tests)
	{
		result = malloc(memsize);
		expected = malloc(memsize);
		int	byte = rand() % 10000 - 5000;
		int	num_bytes = rand() % memsize;
		result = ft_memset(result, byte, num_bytes);
		expected = memset(expected, byte, num_bytes);
		int j = 0;
		while (j < num_bytes)
		{
			if(!assert_true("", result[j] == expected[j]))
				test = false;
			j++;
		}
		free(result);
		free(expected);
		i++;
	}
	assert_true("Ran 1,000 random tests: ", test);


	char	expected_str[100] = "abcdef";
	char	result_str[100] = "abcdef";

	memset(expected_str, 'z', 90);
	ft_memset(result_str, 'z', 90);
	print_msg_color("Testing writing to string: \n", YELLOW);
	printf("Expected string = \n%s\n", expected_str);
	printf("Result string = \n%s\n", result_str);
}

void	test_bzero()
{
	print_msg_color("\n---Testing ft_bzero---\n", BLUE);
	int	memsize = 1000;
	char	*result = malloc(memsize);
	char	*expected = malloc(memsize);

	// fill bytes 100 to 1000 with 1
	memset(&result[99], 1, 900);
	memset(&expected[99], 1, 900);
	int 	i = 0;
	bool	test = true;
	ft_bzero(result, 100);
	bzero(expected, 100);
	while (i < memsize)
	{
		if(!assert_true("", result[i] == expected[i]))
			test = false;
		i++;
	}
	assert_true("First 100 bytes are zero and the rest should be ones : ", test);
	free(result);
	free(expected);
}

void	test_memcpy()
{
	print_msg_color("\n---Testing ft_memcpy---\n", BLUE);
	int	memsize =  100;
	char *original_memory = malloc(memsize);
	int i = 0;
	while (i < 100)
	{
		original_memory[i] = i + 1;
		i++;
	}
	// original_memory = [1...100]
	
	char	*expected = malloc(memsize);
	char	*result = malloc(memsize);
	memset(result, 42, memsize);
	memset(expected, 42, memsize);
	ft_memcpy(result, original_memory, memsize - 40);
	memcpy(expected, original_memory, memsize - 40);

	i = 0;
	bool test = true;
	while (i < memsize)
	{
		if (!assert_true("", expected[i] == result[i]))
			test = false;
		i++;
	}
	assert_true("Memory has been copied correctly: ", test);
	free(original_memory);
	free(expected);
	free(result);
}

void	test_memmove()
{
	
}

int	main()
{
	srand(42);
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();
	test_strlen();
	test_memset();
	test_bzero();
	test_memcpy();
}
