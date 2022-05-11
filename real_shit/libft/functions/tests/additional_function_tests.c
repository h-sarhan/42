/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:05:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/11 21:03:28 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

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
