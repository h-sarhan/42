/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:12:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/10 15:24:14 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_isalpha()
{
	print_msg_color("\n---Testing ft_isalpha---\n", BLUE);
	bool	test = true;
	bool	ft_res;
	bool	libc_res;
	int i =  EOF;
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
	int	i = EOF;
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
	int	i = EOF;
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
	int	i = EOF;
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
	int	i = EOF;
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
