/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:05:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/12 12:04:23 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_ft_split()
{
	print_msg_color("\n---Testing ft_substr---\n", BLUE);

	char	**result = ft_split("easy example", ' ');
	char	**expected = malloc(sizeof(char *) * 2);
	expected[0] = "easy";
	expected[1] = "example";
	assert_str_array_equal("Test ft_split (easy example): ", result, expected, 2);
	assert_is_null("Test ft_split adds NULL at the end: ", result[2]);
	free(result);
	free(expected);
	
	result = ft_split("     harder    example       1", ' ');
	expected = malloc(sizeof(char *) * 3);
	expected[0] = "harder";
	expected[1] = "example";
	expected[2] = "1";
	assert_str_array_equal("Test ft_split (harder example 1): ", result, expected, 3);
	assert_is_null("Test ft_split adds NULL at the end: ", result[3]);
	free(result);
	free(expected);
	
	result = ft_split("harder    example    2    ", ' ');
	expected = malloc(sizeof(char *) * 3);
	expected[0] = "harder";
	expected[1] = "example";
	expected[2] = "2";
	assert_str_array_equal("Test ft_split (harder example 2): ", result, expected, 3);
	assert_is_null("Test ft_split adds NULL at the end: ", result[3]);
	free(result);
	free(expected);
	
	result = ft_split("          harder    example    3    ", ' ');
	expected = malloc(sizeof(char *) * 3);
	expected[0] = "harder";
	expected[1] = "example";
	expected[2] = "3";
	assert_str_array_equal("Test ft_split (harder example 3): ", result, expected, 3);
	assert_is_null("Test ft_split adds NULL at the end: ", result[3]);
	free(result);
	free(expected);

	result = ft_split("", ' ');
	assert_is_null("Test ft_split with empty string: ", result[0]);
	free(result);

	result = ft_split(" ", ' ');
	assert_is_null("Test ft_split with single separator: ", result[0]);
	free(result);

	result = ft_split("          ", ' ');
	assert_is_null("Test ft_split with many separators: ", result[0]);
	free(result);

	result = ft_split("a", ' ');
	expected = malloc(sizeof(char *) * 1);
	expected[0] = "a";
	assert_str_array_equal("Test ft_split with single character: ", result, expected, 1);
	assert_is_null("Test ft_split adds NULL at the end: ", result[1]);
	free(result);
	free(expected);
	
	result = ft_split("         a", ' ');
	expected = malloc(sizeof(char *) * 1);
	expected[0] = "a";
	assert_str_array_equal("Test ft_split with single character and separators to the left: ", result, expected, 1);
	assert_is_null("Test ft_split adds NULL at the end: ", result[1]);
	free(result);
	free(expected);
	
	result = ft_split("a        ", ' ');
	expected = malloc(sizeof(char *) * 1);
	expected[0] = "a";
	assert_str_array_equal("Test ft_split with single character and separators to the right: ", result, expected, 1);
	assert_is_null("Test ft_split adds NULL at the end: ", result[1]);
	free(result);
	free(expected);
	
	result = ft_split("         a          ", ' ');
	expected = malloc(sizeof(char *) * 1);
	expected[0] = "a";
	assert_str_array_equal("Test ft_split with single character and separators to the left and right: ", result, expected, 1);
	assert_is_null("Test ft_split adds NULL at the end: ", result[1]);
	free(result);
	free(expected);
	
}

void	test_ft_substr()
{
	print_msg_color("\n---Testing ft_substr---\n", BLUE);
	
	char *result = ft_substr("abcdef", 2, 2);

	assert_str_equal("Check that substr returns the correct substring when len < substring length: ",
					result, "cd");
	free(result);
	
	result = ft_substr("abcdef", 0, ft_strlen("abcdef"));
	assert_str_equal("Check that substr returns the correct substring when len == substring length: ",
					result, "abcdef");
	free(result);
	
	result = ft_substr("abcdef", 4, 23);
	assert_str_equal("Check that substr returns the correct substring when len > substring length: ",
					result, "ef");
	free(result);
	print_msg_color("Starting random tests: ", YELLOW);
}

void	test_ft_strtrim()
{
	print_msg_color("\n---Testing ft_strtrim---\n", BLUE);
	
	char *res = ft_strtrim("    \n \n'''    MOM LOVES\n' ME     \n'", "' \n");
	char	expected[100] = "MOM LOVES\n' ME";
	assert_str_equal("Check that strtrim trips properly under normal circumstances: ",
					res, expected);
	free(res);
	
	res = ft_strtrim("MOM LOVES\n' ME", "' \n");
	strcpy(expected, "MOM LOVES\n' ME");
	assert_str_equal("Check that strtrim trips properly when string is already trimmed: ",
					res, expected);
	free(res);

	res = ft_strtrim("MOM LOVES\n' ME", "");
	strcpy(expected, "MOM LOVES\n' ME");
	assert_str_equal("Check that strtrim does not trim when separator strings are empty: ",
					res, expected);

	free(res);
	
	res = ft_strtrim("", "\n ");
	expected[0] = '\0';
	assert_str_equal("Check that strtrim returns an empty string when given one: ",
					res, expected);
	free(res);
}

void	test_ft_putchar_fd()
{
	print_msg_color("\n---Testing ft_putchar_fd---\n", BLUE);
	int fd = open("tests/test_output/putchar.test", O_WRONLY | O_CREAT, 0644);
	ft_putchar_fd('4', fd);
	ft_putchar_fd('2', fd);
	ft_putchar_fd('\n', fd);
	ft_putchar_fd('\0', fd);
	char	chars[10];
	close(fd);
	fd = open("tests/test_output/putchar.test", O_RDONLY);
	int	bytes_read = read(fd, chars, 4);
	assert_str_equal("Check that 42 and a new line have been written "
			"correctly to the file putchar.test: ", chars, "42\n");
	assert_int_equal("Check that the correct number of bytes has been read: ",
			bytes_read, 4);
	close(fd);
}

void	test_ft_putstr_fd()
{
	print_msg_color("\n---Testing ft_putstr_fd---\n", BLUE);
	int fd = open("tests/test_output/putstr.test", O_WRONLY | O_CREAT, 0644);
	char str[] = "42 abu dhabi wooooooooooooooooooooooooooooooooo!\n";
	ft_putstr_fd(str, fd);
	char	*chars = malloc(sizeof(char) * ft_strlen(str));
	close(fd);
	fd = open("tests/test_output/putstr.test", O_RDONLY);
	int	bytes_read = read(fd, chars, ft_strlen(str));
	assert_str_equal("Check that the string has been written "
			"correctly to the file putstr.test: ", chars, str);
	assert_int_equal("Check that the correct number of bytes has been read: ",
			bytes_read, ft_strlen(str));
	close(fd);
}

void	test_ft_putendl_fd()
{
	print_msg_color("\n---Testing ft_putendl_fd---\n", BLUE);
	int fd = open("tests/test_output/putendl.test", O_WRONLY | O_CREAT, 0644);
	char str[] = "42 abu dhabi wooooooooooooooooooooooooooooooooo!";
	ft_putendl_fd(str, fd);
	char	*chars = malloc(sizeof(char) * (ft_strlen(str) + 1));
	close(fd);
	fd = open("tests/test_output/putendl.test", O_RDONLY);
	int	bytes_read = read(fd, chars, ft_strlen(str) + 1);
	char *str_with_endl = malloc(sizeof(char) * (ft_strlen(str) + 2));
	strcpy(str_with_endl, str);
	str_with_endl[ft_strlen(str)] = '\n';
	assert_str_equal("Check that the string has been written "
			"correctly to the file putendl.test with a new line: ", chars, str_with_endl);
	assert_int_equal("Check that the correct number of bytes has been read: ",
			bytes_read, ft_strlen(str) + 1);
	close(fd);
}

void	test_ft_putnbr_fd()
{
	print_msg_color("\n---Generating ft_putnbr_fd test output---\n", BLUE);
	
	int	num = INT_MIN;
	int fd = open("tests/test_output/putnbr.test", O_WRONLY | O_CREAT, 0644);
	while (num < INT_MIN + 1000)
	{
		ft_putnbr_fd(num, fd);
		ft_putchar_fd('\n', fd);
		num++;
	}
	num = -1000;
	while (num < 1000)
	{
		ft_putnbr_fd(num, fd);
		ft_putchar_fd('\n', fd);
		num++;
	}
	num = INT_MAX - 1000;
	while (num < INT_MAX)
	{
		ft_putnbr_fd(num, fd);
		ft_putchar_fd('\n', fd);
		num++;
	}
	ft_putnbr_fd(num, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}
