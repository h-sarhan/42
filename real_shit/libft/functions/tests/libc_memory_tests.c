/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:11:54 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/11 13:39:45 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_memchr()
{
	print_msg_color("\n---Testing ft_memchr---\n", BLUE);
	
	char	memory[100];

	memset(memory, 8, 100);
	memory[10] = 19;
	assert_true("ft_memchr finds single non-terminating byte correctly: ",
				ft_memchr(memory, 19, 100) == memchr(memory, 19, 100));
	assert_true("ft_memchr returns NULL when character is not found: ",
				ft_memchr(memory, 20, 100) == memchr(memory, 20, 100));

	char	ran_bytes[1000];
	int	num_tests = 10000;
	int	i = 0;
	int	j = 0;
	bool	test = true;
	char	ran_byte;
	int		search_size;
	print_msg_color("Running random tests: \n", YELLOW);
	while (i < num_tests)
	{
		j = 0;
		search_size = rand() % 1000;
		// fill bytes with random characters
		while (j < 1000)
		{
			ran_bytes[j] = rand() % 100;
			j++;
		}
		ran_bytes[j] = '\0';
		// pick random byte to look for
		ran_byte = rand() % 100;
		if (!assert_true("", ft_memchr(ran_bytes, ran_byte, search_size) == memchr(ran_bytes, ran_byte, search_size)))
				test = false;
		i++;
	}
	assert_true("Random tests passed: ", test);
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
	i = EOF;
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
	// TODO: Write this function
}

void	test_calloc()
{
	print_msg_color("\n---Testing ft_calloc---\n", BLUE);
	
	int	*expected1;
	int	*result1;

	expected1 = calloc(1, sizeof(int));
	result1 = ft_calloc(1, sizeof(int));

	assert_int_equal("Check that 1 int has been initialzed propoerly: ", result1[0], 0);
	expected1[0] = 42;
	result1[0] = 42;

	assert_int_equal("Check that 1 int is allocated correctly: ", result1[0], expected1[0]);
	free(expected1);
	free(result1);
	
	int	*expected;
	int	*result;

	size_t	nmembs;
	int	i = 0;
	int	num_tests = 500;
	bool test = true;
	print_msg_color("Starting random tests: \n", YELLOW);
	while (i < num_tests)
	{
		nmembs = rand() % 1000;
		expected = calloc(nmembs, sizeof(int));
		result = ft_calloc(nmembs, sizeof(int));
		size_t	j = 0;
		while (j < nmembs)
		{
			if (expected == NULL)
			{
				printf("expected is null\n");
				break;
			}
			if (result == NULL)
			{
				printf("result is null\n");
				break;
			}
			if (!assert_int_equal("", result[j], expected[j]))
			{
				printf("Test number = %d\nNMEMBS = %zu\nmember index = %zu\n", i, nmembs, j);
				test = false;
				break;
			}
				
			int	item = rand() % 100;
			expected[j] = item;
			result[j] = item;
			if (!assert_int_equal("", result[j], expected[j]))
			{
				printf("Test number = %d\nNMEMBS = %zu\nitem = %d\nmember index = %zu\n", i, nmembs, item, j);
				test = false;
				break;
			}
			j++;
		}
		free(expected);
		free(result);
		if (!test)
			break;
		i++;
	}
	assert_true("Random tests have passed: ", test);
}
