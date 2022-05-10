/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:25:10 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/10 15:25:45 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

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

void	test_toupper()
{
	print_msg_color("\n---Testing ft_toupper---\n", BLUE);
	char	all_a[] = "aaaaaaaaaa";
	char	all_A[] = "AAAAAAAAAA";
	char	res[11];
	res[10] = '\0';

	for (int i = 0; i < 10; i++)
		res[i] = ft_toupper(all_a[i]);
	assert_str_equal("Test that conversion succeeds with lowercase letters: ",
					res, all_A);
	strcpy(res, all_A);
	for (int i = 0; i < 10; i++)
		res[i] = ft_toupper(res[i]);
	assert_str_equal("Test that uppercase letters do not get converted: ",
					res, all_A);

	int		i = EOF;
	bool	test = true;
	while (i < 256)
	{
		int ft_upper = ft_toupper(i);
		int	c_upper = toupper(i);
		if (!assert_true("", ft_upper == c_upper))
			test = false;
		i++;
	}
	assert_true("Test ft_toupper with all possible values: ", test);
}

void	test_tolower()
{
	print_msg_color("\n---Testing ft_tolower---\n", BLUE);
	char	all_a[] = "aaaaaaaaaa";
	char	all_A[] = "AAAAAAAAAA";
	char	res[11];
	res[10] = '\0';

	for (int i = 0; i < 10; i++)
		res[i] = ft_tolower(all_A[i]);
	assert_str_equal("Test that conversion succeeds with uppercase letters: ",
					res, all_a);
	strcpy(res, all_a);
	for (int i = 0; i < 10; i++)
		res[i] = ft_tolower(res[i]);
	assert_str_equal("Test that lowercase letters do not get converted: ",
					res, all_a);

	int		i = EOF;
	bool	test = true;
	while (i < 256)
	{
		int ft_lower = ft_tolower(i);
		int	c_lower = tolower(i);
		if (!assert_true("", ft_lower == c_lower))
			test = false;
		i++;
	}
	assert_true("Test ft_tolower with all possible values: ", test);
}

void	test_strchr()
{
	print_msg_color("\n---Testing ft_strchr---\n", BLUE);
	
	char	*haystack = "0123456";

	assert_true("ft_strchr finds single non-terminating character correctly: ",
				ft_strchr(haystack, '6') == strchr(haystack, '6'));
	assert_true("ft_strchr finds terminating character correctly: ",
				ft_strchr(haystack, '\0') == strchr(haystack, '\0'));
	assert_true("ft_strchr returns NULL when character is not found: ",
				ft_strchr(haystack, 'a') == strchr(haystack, 'a'));

	char	ran_string[1001];
	ran_string[1000] = '\0';
	int	num_tests = 100000;
	int	i = 0;
	int	j = 0;
	bool	test = true;
	char	ran_char;
	int		str_size;
	print_msg_color("Running random tests: \n", YELLOW);
	while (i < num_tests)
	{
		j = 0;
		str_size = rand() % 1000;
		// fill string with random characters
		while (j < str_size)
		{
			ran_string[j] = 1 + (rand() % 127);
			j++;
		}
		ran_string[j] = '\0';
		// pick random char to look for (including \0)
		ran_char = rand() % 128;
		if (!assert_true("", ft_strchr(ran_string, ran_char) == strchr(ran_string, ran_char)))
				test = false;
		i++;
	}
	assert_true("Random tests passed: ", test);
}

void	test_strrchr()
{
	print_msg_color("\n---Testing ft_strrchr---\n", BLUE);
	
	char	*haystack = "01234561";

	assert_true("ft_strrchr finds single non-terminating character correctly: ",
				ft_strrchr(haystack, '1') == strrchr(haystack, '1'));
	assert_true("ft_strrchr finds terminating character correctly: ",
				ft_strrchr(haystack, '\0') == strrchr(haystack, '\0'));
	assert_true("ft_strrchr returns NULL when character is not found: ",
				ft_strrchr(haystack, 'a') == strrchr(haystack, 'a'));

	char	ran_string[1001];
	ran_string[1000] = '\0';
	int	num_tests = 100000;
	int	i = 0;
	int	j = 0;
	bool	test = true;
	char	ran_char;
	int		str_size;
	print_msg_color("Running random tests: \n", YELLOW);
	while (i < num_tests)
	{
		j = 0;
		str_size = rand() % 1000;
		// fill string with random characters
		while (j < str_size)
		{
			ran_string[j] = 1 + (rand() % 127);
			j++;
		}
		ran_string[j] = '\0';
		// pick random char to look for (including \0)
		ran_char = rand() % 128;
		if (!assert_true("", ft_strrchr(ran_string, ran_char) == strrchr(ran_string, ran_char)))
				test = false;
		i++;
	}
	assert_true("Random tests passed: ", test);
}
