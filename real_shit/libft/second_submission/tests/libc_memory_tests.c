/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_memory_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:11:54 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/14 19:58:55 by hsarhan          ###   ########.fr       */
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
	int		byte_to_find;
	int	num_tests = 10000;
	int	i = 0;
	int	j = 0;
	bool	test = true;
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
		byte_to_find = rand() % 100 - 50;
		if (!assert_true("", ft_memchr(ran_bytes, byte_to_find, search_size) == memchr(ran_bytes, byte_to_find, search_size)))
				test = false;
		i++;
	}
	assert_true("Random tests passed: ", test);
}

void	test_memset()
{
	print_msg_color("\n---Testing ft_memset---\n", BLUE);
	int	memsize = 500;
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
	
	char	*expected_byte_ptr = malloc(1);
	char	*result_byte_ptr = malloc(1);
	test = true;
	i = 0;
	while (i < 1)
	{
		result_byte_ptr = ft_memset(result_byte_ptr, i, 1);
		expected_byte_ptr = memset(expected_byte_ptr, i, 1);
		if (!assert_true("", *result_byte_ptr == *expected_byte_ptr))
			test = false;
		i++;
	}
	assert_true("Writing all possible single byte values: ", test);
	
	test = true;
	i = -10000;
	while (i < 10000)
	{
		result_byte_ptr = ft_memset(result_byte_ptr, i, 1);
		expected_byte_ptr = memset(expected_byte_ptr, i, 1);
		if (!assert_true("", *result_byte_ptr == *expected_byte_ptr))
			test = false;
		i++;
	}
	assert_true("Writing impossible single byte values: ", test);
	

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

bool	are_same_sign(int res, int expected)
{
	return ((res > 0 && expected > 0) ||
			(res < 0 && expected < 0) ||
			(res == 0 && expected == 0));
}

void	test_memcmp()
{
	print_msg_color("\n---Testing ft_memcmp---\n", BLUE);
	
	unsigned char *bytes1;
	unsigned char *bytes2;

	unsigned int num_bytes = 100;
	bytes1 = malloc(num_bytes);
	bytes2 = malloc(num_bytes);
	memset(bytes1, 42, num_bytes);
	memset(bytes2, 42, num_bytes);
	int	res = ft_memcmp(bytes1, bytes2, num_bytes);
	int	expected = memcmp(bytes1, bytes2, num_bytes);
	assert_true("Test ft_memcmp when all bytes are equal: ",
			are_same_sign(res, expected)); 

	bytes1[10] = 200;
	bytes2[10] = 1;
	res = ft_memcmp(bytes1, bytes2, num_bytes);
	expected = memcmp(bytes1, bytes2, num_bytes);
	assert_true("Test ft_memcmp when one byte is greater than the other: ",
			are_same_sign(res, expected)); 
	
	bytes1[10] = 1;
	bytes2[10] = 200;
	res = ft_memcmp(bytes1, bytes2, num_bytes);
	expected = memcmp(bytes1, bytes2, num_bytes);
	assert_true("Test ft_memcmp when one byte is less than the other: ",
			are_same_sign(res, expected)); 
	
	memset(bytes1, 42, num_bytes);
	memset(bytes2, 42, num_bytes);

	bytes1[99] = 0;
	bytes2[99] = 255;
	res = ft_memcmp(bytes1, bytes2, num_bytes);
	expected = memcmp(bytes1, bytes2, num_bytes);
	assert_true("Test ft_memcmp when last byte is greater than the other: ",
			are_same_sign(res, expected)); 
	
	bytes1[99] = 255;
	bytes2[99] = 0;
	res = ft_memcmp(bytes1, bytes2, num_bytes);
	expected = memcmp(bytes1, bytes2, num_bytes);
	assert_true("Test ft_memcmp when last byte is less than the other: ",
			are_same_sign(res, expected)); 
	
	free(bytes1);
	free(bytes2);

	int	num_tests = 10000;
	int i = 0;
	bool test;
	while (i < num_tests)
	{
		int num_bytes = 1 + rand() % 10;
		bytes1 = malloc(num_bytes);
		bytes2 = malloc(num_bytes);
		int j = 0;
		while (j < num_bytes)
		{
			bytes1[j] = rand() % 20;
			bytes2[j] = rand() % 20;
			j++;
		}
		res = ft_memcmp(bytes1, bytes2, num_bytes);
		expected = memcmp(bytes1, bytes2, num_bytes);
		test = assert_true("", are_same_sign(res, expected));

		free(bytes1);
		free(bytes2);
		if (!test)
			break ;
		i++;
	}
	assert_true("Test ft_memcmp with random values: ", test);
}

void	test_bzero()
{
	print_msg_color("\n---Testing ft_bzero---\n", BLUE);
	int	memsize = 1000;
	char	*result = malloc(memsize);
	char	*expected = malloc(memsize);

	// fill bytes 100 to 1000 with 1
	memset(result, 1, 1000);
	memset(expected, 1, 1000);
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
//    			         012345678
	char	overlap[] = "hassan!"    ;
//	                         ^  ^
//	             src         s  e
//	                          ^  ^
//	             dst          s  e


	printf("This should overlap: \n");
	// ft_memcpy modified source code 
	char *dst = &overlap[5];
	char *src = &overlap[4];
	int len = 3;
	i = 0;
	printf(YELLOW "Copying left to right\n" RESET);
	while (i < len)
	{
		printf(YELLOW "str[%d] = str[%d]\n" RESET, 4 + i + (int)(dst - src), 4 + i );
		dst[i] = src[i];
		i++;
	}
}

void	test_memmove()
{
	print_msg_color("\n---Testing ft_memmove---\n", BLUE);
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
	ft_memmove(result, original_memory, memsize - 40);
	memmove(expected, original_memory, memsize - 40);

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
	//			         012345678
	char	overlap[] = "hassan!"    ;
//	                         ^  ^
//	             src         s  e
//	                          ^  ^
//	             dst          s  e


	printf("This should not overlap: \n");

	// ft_memmove modified source code 
	char *dst = &overlap[5];
	char *src = &overlap[4];
	int len = 3;
	i = 0;
	if (src < dst && src + len >= dst)
	{
		i = len - 1;
		printf(YELLOW "Copying right to left\n" RESET);
		while (i >= 0)
		{
			printf(YELLOW "str[%d] = str[%d]\n" RESET, 4 + i + (int)(dst - src), 4 + i );
			dst[i] = src[i];
			i--;
		}
	}
	else
	{
		i = 0;
		printf(YELLOW "Copying left to right\n" RESET);
		while (i < len)
		{
			printf(YELLOW "str[%d] = str[%d]\n" RESET, 4 + i + (int)(dst - src), 4 + i );
			dst[i] = src[i];
			i++;
		}
	}
}

void	test_calloc()
{
	print_msg_color("\n---Testing ft_calloc---\n", BLUE);
	
	int	*expected1;
	int	*result1;

	expected1 = calloc(1, sizeof(int));
	result1 = ft_calloc(1, sizeof(int));

	assert_int_equal("Check that 1 int has been initialzed properly: ", result1[0], 0);
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
	
	assert_is_null("Test calloc with overflow: ", ft_calloc(SIZET_MAX, 2));
	assert_is_null("Test calloc with nmembers == 0 (not sure about this): ", ft_calloc(0, 42));
	assert_is_null("Test calloc with item size ==  0 (not sure about this): ", ft_calloc(42, 0));
}
