/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:05:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/11 19:34:59 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

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
