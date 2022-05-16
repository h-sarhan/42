/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_function_tests.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 19:05:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/14 19:46:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

char	return_upper_if_even(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (ft_toupper(c));
	else
		return (c);
}

void	test_ft_strmapi()
{
	print_msg_color("\n---Testing ft_strmapi---\n", BLUE);
	char	*str = "kjhbkjhbkgvkgvkhgvkhgvkghvkuygvbk";

	char	*result = ft_strmapi(str, &return_upper_if_even);
	size_t i = 0;
	bool test = true;
	assert_int_equal("Check that input string is same length as result string: ", ft_strlen(result), ft_strlen(str));
	while (i < ft_strlen(result))
	{
		if (i % 2 == 0)
			if (!assert_true("", result[i] >= 'A' && result[i] <= 'Z'))
			{
				test = false;
				break ;
			}
		i++;
	}
	assert_true("Check that function was applied correctly: ", test);
	free(result);
}

void	change_to_upper_if_even(unsigned int i, char *c)
{

	if (i % 2 == 0)
	{
		char upper = ft_toupper(*c);
		*c = upper;
	}
}

void	test_ft_striteri()
{
	print_msg_color("\n---Testing ft_striteri---\n", BLUE);
	char	str[] = "kjhbkjhbkgvkgvkhgvkhgvkghvkuygvbk";

	ft_striteri(str, &change_to_upper_if_even);
	size_t i = 0;
	bool test = true;
	while (i < ft_strlen(str))
	{
		if (i % 2 == 0 && !assert_true("", str[i] >= 'A' && str[i] <= 'Z'))
		{
			test = false;
			break ;
		}
		i++;
	}
	assert_true("Check that function was applied correctly: ", test);
}

void	test_ft_split()
{
	print_msg_color("\n---Testing ft_split---\n", BLUE);

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

void	test_ft_itoa()
{
	print_msg_color("\n---Testing ft_itoa---\n", BLUE);
	
	char *result = ft_itoa(INT_MIN);
	assert_str_equal("Testing with INT_MIN: ", ft_itoa(INT_MIN), "-2147483648");
	free(result);


	int	i = INT_MIN + 1;
	bool test = true;
	while (i < INT_MIN + 100000)
	{
		result = ft_itoa(i);
		if (!assert_int_equal("", atoi(result), i))
		{
			test = false;
			free(result);
			break ;
		}
		free(result);
		i++;
	}
	assert_true("Testing numbers from INT_MIN + 1 -> INT_MIN + 10000: ", test);
	i = -100000;
	test = true;
	while (i < 100000)
	{
		result = ft_itoa(i);
		if (!assert_int_equal("", atoi(result), i))
		{
			test = false;
			free(result);
			break ;
		}
		free(result);
		i++;
	}
	assert_true("Testing numbers from -10000 -> 10000: ", test);
	i = INT_MAX - 100000;
	test = true;
	while (i < INT_MAX)
	{
		result = ft_itoa(i);
		if (!assert_int_equal("", atoi(result), i))
		{
			test = false;
			free(result);
			break ;
		}
		free(result);
		i++;
	}
	assert_true("Testing numbers from INT_MAX - 10000 -> INT_MAX - 1: ", test);

	result = ft_itoa(INT_MAX);
	assert_str_equal("Testing with INT_MAX: ", ft_itoa(INT_MAX), "2147483647");
	free(result);
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

	int		num_tests = 1000;
	int		i = 0;
	int		str_start;
	char	str[101];
	int		j;
	char	*substr;
	int 	len;
	bool	test;
	while (i < num_tests)
	{
		str_start = rand() % 100;
		len = rand() % 150;
		j = 0;
		while (j < 100)
		{
			str[j] = 1 + rand() % 127;
			j++;
		}
		str[j] = '\0';
		substr = ft_substr(str, str_start, len);
		if (len + str_start > 100)
		{
			test = assert_str_equal("", substr, &str[str_start]);
		}
		else
		{
			str[str_start + len] = '\0';
			test = assert_str_equal("", substr, &str[str_start]);
		}
		free(substr);
		if (!test)
			break;
		i++;
	}
	assert_true("Randomised tests passed: ", test);
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

void test_ft_strjoin()
{
	print_msg_color("\n---Testing ft_strjoin---\n", BLUE);

	char	*res = ft_strjoin("abc", "def");
	assert_str_equal("\"abc\" + \"def\" = \"abcdef\" ", res, "abcdef");
	free(res);

	res = ft_strjoin("", "def");
	assert_str_equal("\"\" + \"def\" = \"def\"", res, "def");
	free(res);
	
	res = ft_strjoin("abc", "");
	assert_str_equal("\"abc\" + \"\" = \"abc\"", res, "abc");
	free(res);
	
	res = ft_strjoin("", "");
	assert_str_equal("\"\" + \"\" = \"\"", res, "");
	free(res);
}

void	test_ft_putchar_fd(int flag)
{
	print_msg_color("\n---Testing ft_putchar_fd---\n", BLUE);
	if (flag == 1)
	{
		int fd = 1;
		ft_putchar_fd('4', fd);
		ft_putchar_fd('2', fd);
		ft_putchar_fd('\n', fd);
	}
	else if (flag == 2)
	{
		printf("42\n");
	}
}

void	test_ft_putstr_fd(int flag)
{
	print_msg_color("\n---Testing ft_putstr_fd---\n", BLUE);
	int fd = 1;
	char str[] = "42 abu dhabi wooooooooooooooooooooooooooooooooo!\n";
	if (flag == 1)
	{
		ft_putstr_fd(str, fd);
	}
	else if (flag == 2)
	{
		printf("%s", str);
	}
}

void	test_ft_putendl_fd(int flag)
{
	print_msg_color("\n---Testing ft_putendl_fd---\n", BLUE);
	char str[] = "42 abu dhabi wooooooooooooooooooooooooooooooooo!";
	int fd = 1;
	if (flag == 1)
	{
		ft_putendl_fd(str, fd);
	}
	else if (flag == 2)
	{
		printf("%s\n", str);
	}
}

void	test_ft_putnbr_fd(int flag)
{
	print_msg_color("\n---Generating ft_putnbr_fd test output---\n", BLUE);
	int fd = 1;
	
	int	num = INT_MIN;
	while (num < INT_MIN + 1000)
	{
		if (flag == 1)
		{
			ft_putnbr_fd(num, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (flag == 2)
		{
			printf("%d\n", num);
		}
		num++;
	}
	num = -1000;
	while (num < 1000)
	{
		if (flag == 1)
		{
			ft_putnbr_fd(num, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (flag == 2)
		{
			printf("%d\n", num);
		}
		num++;
	}
	num = INT_MAX - 1000;
	while (num < INT_MAX - 100)
	{
		if (flag == 1)
		{
			ft_putnbr_fd(num, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (flag == 2)
		{
			printf("%d\n", num);
		}
		num++;
	}
	if (flag == 1)
	{
		ft_putnbr_fd(num, fd);
		ft_putchar_fd('\n', fd);
	}
	else if (flag == 2)
	{
		printf("%d\n", num);
	}
}
