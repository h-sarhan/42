/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_string_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:25:10 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/13 23:14:22 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

bool	test_strcmp_results(int res, int expected)
{
	if ((res > 0 && expected > 0)
		|| (res < 0 && expected < 0)
		|| (res == 0 && expected == 0))
		return (true);
	return (false);
}

void	test_strncmp()
{
	print_msg_color("\n---Testing ft_strncmp---\n", BLUE);
	int		expected = strncmp("abc", "abc", 3);
	int		res = ft_strncmp("abc", "abc", 3);
	assert_true("Testing strncmp with same size and equal strings (n == strlen): ",
			test_strcmp_results(res, expected));
	
	expected = strncmp("abd", "abc", 3);
	res = ft_strncmp("abd", "abc", 3);
	assert_true("Testing strncmp with same size and different strings (n == strlen): ",
			test_strcmp_results(res, expected));

	expected = strncmp("abc", "aec", 3);
	res = ft_strncmp("abc", "aec", 3);
	assert_true("Testing strncmp with same size and different strings 2 (n == strlen): ",
			test_strcmp_results(res, expected));

	expected = strncmp("abcaaaaa", "aec", 3);
	res = ft_strncmp("abcaaaaa", "aec", 3);
	assert_true("Testing strncmp with different size and different strings (n == 3): ",
			test_strcmp_results(res, expected));
	
	expected = strncmp("abc", "aecaaaa", 3);
	res = ft_strncmp("abc", "aecaaaa", 3);
	assert_true("Testing strncmp with different size and different strings 2 (n == 3): ",
			test_strcmp_results(res, expected));
	
	expected = strncmp("abc", "abc", 30);
	res = ft_strncmp("abc", "abc", 30);
	assert_true("Testing strncmp with same size and same strings (n == 30): ",
			test_strcmp_results(res, expected));
	
	expected = strncmp("abc", "a3c", 30);
	res = ft_strncmp("abc", "a3c", 30);
	assert_true("Testing strncmp with same size and different strings (n == 30): ",
			test_strcmp_results(res, expected));
	
	int	num_tests = 100000;
	int	i = 0;
	int j;
	int	strsize1;
	int	strsize2;
	char	*ran_string1;
	char	*ran_string2;
	int		num_chars_to_compare;
	bool test = true;
	print_msg_color("Starting random tests: \n", YELLOW);
	while (i < num_tests)
	{
		strsize1 = rand() % 100;
		strsize2 = rand() % 100;
		ran_string1 = malloc(sizeof(char) * (strsize1 + 1));
		ran_string2 = malloc(sizeof(char) * (strsize2 + 1));
		ran_string1[strsize1] = '\0';
		ran_string2[strsize2] = '\0';
		j = 0;
		while (j < strsize1)
		{
			ran_string1[j] = 1 + rand() % 127;
			j++;
		}
		j = 0;
		while (j < strsize2)
		{
			ran_string2[j] = 1 + rand() % 127;
			j++;
		}
		num_chars_to_compare = rand() % 100;
		expected = strncmp(ran_string1, ran_string2, num_chars_to_compare);
		res = ft_strncmp(ran_string1, ran_string2, num_chars_to_compare);
		if (!assert_true("", test_strcmp_results(res, expected)))
		{
			test = false;
			break;
		}
		i++;
		free(ran_string1);
		free(ran_string2);
	}
	assert_true("Random tests passed?: ", test);
}

void	test_strlen()
{
	print_msg_color("\n---Testing ft_strlen---\n", BLUE);

	char	str[100001];

	int 	test_num = 0;
	bool	test = true;
	print_msg_color("Testing with random strings (<= 1000 chars)\n", YELLOW);
	while (test_num < 10000)
	{
		int	str_len = rand() % 1001;
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

	int		i = -10000;
	bool	test = true;
	while (i < 10000)
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

	int		i = -10000;
	bool	test = true;
	while (i < 10000)
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
	int	ran_char;
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
		ran_char = rand() % 1000 - 500;
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
	int		ran_char;
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
		ran_char = rand() % 1000 - 500;
		if (!assert_true("", ft_strrchr(ran_string, ran_char) == strrchr(ran_string, ran_char)))
				test = false;
		i++;
	}
	assert_true("Random tests passed: ", test);
}

void	test_strdup()
{
	print_msg_color("\n---Testing ft_strdup---\n", BLUE);

	char	str1[] = "abcdliugyhoilugyuygkuytreyteruvxcxbv";
	char	*str2 = ft_strdup(str1);
	
	assert_str_equal("Check that string is duplicated correctly: ", str1, str2);
	free(str2);
	
	int i = 0;
	int num_tests = 10000;
	int	string_size;
	char	*orig_str;
	char	*dup_str;
	bool test = true;
	print_msg_color("Running random tests: \n", YELLOW);
	while (i < num_tests)
	{
		string_size = rand() % 1000;
		orig_str = malloc(sizeof(char) * (string_size + 1));
		orig_str[string_size] = '\0';
		int j = 0;
		while (j < string_size)
		{
			orig_str[j] = 1 + (rand() % 127);
			j++;
		}
		dup_str = ft_strdup(orig_str);
		if (!assert_str_equal("", dup_str, orig_str))
		{
			test = false;
			break;
		}
		free(dup_str);
		free(orig_str);
		i++;
	}
	assert_true("Random tests have passed: ", test);
}

void	test_strnstr()
{
	print_msg_color("\n---Testing ft_strnstr---\n", BLUE);
	
	char *haystack = "Foo Bar Baz";
	char *res = ft_strnstr(haystack, "Bar", ft_strlen(haystack));
	//char *expected = strnstr(haystack, needle, ft_strlen(haystack));

	assert_str_equal("Check that ft_strnstr works when len == string length: ",
					res, "Bar Baz");
	res = ft_strnstr(haystack, "Bad", ft_strlen(haystack));
	assert_is_null("Check that ft_strnstr returns null when needle is not in haystack: ", res);
	
	res = ft_strnstr(haystack, "Bar", 5);
	assert_is_null("Check that ft_strnstr works when len < string length: ", res);

	res = ft_strnstr("Bar", "Bar", 3);
	assert_str_equal("Check that ft_strnstr works when needle == haystack: ", res, "Bar");

	res = ft_strnstr("Bar", "", 3);
	assert_str_equal("Check that ft_strnstr returns haystack when needle is empty: ", res, "Bar");

	print_msg_color("Additional tests: \n", WHITE);
	res = ft_strnstr("work hard and you will earn a good living", "and", 4);
	assert_is_null("Additional test #1: ", res);
	
	res = ft_strnstr("work hard and you will earn a good living", "and", 100);
	assert_str_equal("Additional test #2: ", res, "and you will earn a good living");

	res = ft_strnstr("work hard and you will earn a good living", "and", 13);
	assert_str_equal("Additional test #3: ", res, "and you will earn a good living");
}

void	test_atoi()
{
	print_msg_color("\n---Testing ft_atoi---\n", BLUE);
	
	char *test_str = "123";
	assert_int_equal("\"123\" -> 123: ", ft_atoi(test_str), atoi(test_str));

	test_str = "+123";
	assert_int_equal("\"+123\" -> 123: ", ft_atoi(test_str), atoi(test_str));
	
	test_str = "   +123";
	assert_int_equal("\"   +123\" -> 123: ", ft_atoi(test_str), atoi(test_str));
	
	test_str = " \n \t  +123";
	assert_int_equal("\" \\n \\t  +123\" -> 123: ", ft_atoi(test_str), atoi(test_str));

	test_str = "    -123";
	assert_int_equal("\"    -123\" -> -123: ", ft_atoi(test_str), atoi(test_str));
	
	test_str = "    -1298769873";
	assert_int_equal("\"    -1298769873\" -> -1298769873: ", ft_atoi(test_str), atoi(test_str));
	
	test_str = "    -100000000";
	assert_int_equal("\"    -100000000\" -> -100000000: ", ft_atoi(test_str), atoi(test_str));

	test_str = "    -00000000";
	assert_int_equal("\"    -00000000\" -> 0: ", ft_atoi(test_str), atoi(test_str));
	
	test_str = "    -001000000";
	assert_int_equal("\"    -001000000\" -> -1000000: ", ft_atoi(test_str), atoi(test_str));
	
	test_str = "    -0010a00000";
	assert_int_equal("\"    -0010a00000\" -> -10: ", ft_atoi(test_str), atoi(test_str));

	int i = INT_MIN;
	bool test;
	while (i < INT_MIN + 10000)
	{
		char	*num_string = ft_itoa(i);
		test = assert_int_equal("", ft_atoi(num_string), atoi(num_string));
		free(num_string);
		if (!test)
			break;
		i++;
	}
	assert_true("Test on numbers between INT_MIN and INT_MIN + 10,000: ", test);
	i = -10000;
	while (i < 10000)
	{
		char	*num_string = ft_itoa(i);
		test = assert_int_equal("", ft_atoi(num_string), atoi(num_string));
		free(num_string);
		if (!test)
			break;
		i++;
	}
	assert_true("Test on numbers between -10,000 and 10,000: ", test);
	i = INT_MAX - 10000;
	while (i < INT_MAX)
	{
		char	*num_string = ft_itoa(i);
		test = assert_int_equal("", ft_atoi(num_string), atoi(num_string));
		free(num_string);
		if (!test)
			break;
		i++;
	}
	assert_true("Test on numbers between INT_MAX - 10,000 and INT_MAX - 1: ", test);
	char	*num_string = ft_itoa(INT_MAX);
	assert_int_equal("Test on INT_MAX: ", ft_atoi(num_string), atoi(num_string));
	free(num_string);

}

//void	test_strlcpy()
//{
//	char	*src = "abcdefghijklmnopqrstuvwxyz";
//	char	dest1[100];
//	char	dest2[100];
//	size_t	ret1;
//	size_t	ret2;
//	
//	print_msg_color("\n---Testing ft_strlcpy---\n", BLUE);
//
//	// ensure that these two char arrays are not null terminated intially
//	memset(dest1, 'a', 100);
//	memset(dest2, 'a', 100);
//	ret1 = ft_strlcpy(dest1, src, 10);
//	ret2 = strlcpy(dest2, src, 10);
//	assert_int_equal("Check return values are the same when dstsize < src_len: ", ret1, ret2);
//	assert_str_equal("Check destination strings are the same when dstsize < src_len: ", dest1, dest2);
//	
//	memset(dest1, 'a', 100);
//	memset(dest2, 'a', 100);
//	ret1 = ft_strlcpy(dest1, src, ft_strlen(src) + 1);
//	ret2 = strlcpy(dest2, src, ft_strlen(src) + 1);
//	assert_int_equal("Check return values are the same when dstsize + 1 == src_len: ", ret1, ret2);
//	assert_str_equal("Check destination strings are the same when dstsize + 1 == src_len: ", dest1, dest2);
//
//	// Compiler complains about this test
////	memset(dest1, 'a', 100);
////	memset(dest2, 'a', 100);
////	ret1 = ft_strlcpy(dest1, src, 1000);
////	ret2 = strlcpy(dest2, src, 1000);
////	assert_int_equal("Check return values are the same when dstsize > src_len: ", ret1, ret2);
////	assert_str_equal("Check destination strings are the same when dstsize > src_len: ", dest1, dest2);
//	
//	memset(dest1, 'a', 100);
//	memset(dest2, 'a', 100);
//	dest1[99] = '\0';
//	dest2[99] = '\0';
//	ret1 = ft_strlcpy(dest1, src, 0);
//	ret2 = strlcpy(dest2, src, 0);
//	assert_int_equal("Check return values are the same when dstsize == 0: ", ret1, ret2);
//	assert_str_equal("Check destination strings are the same when dstsize == 0: ", dest1, dest2);
//
//	int i = 0;
//	bool test;
//	while (i < 10000)
//	{
//		memset(dest1, 'a', 100);
//		memset(dest2, 'a', 100);
//		dest1[99] = '\0';
//		dest2[99] = '\0';
//		ret1 = ft_strlcpy(dest1, src, 0);
//		ret2 = strlcpy(dest2, src, 0);
//		test = assert_int_equal("", ret1, ret2);
//		test = assert_str_equal("", dest1, dest2);
//		if (!test)
//			break;
//		i++;
//	}
//	assert_true("Testing dstsizes from 0 -> 10000: ", test);
//}

//void	test_strlcat()
//{
//	print_msg_color("\n---Testing ft_strlcat---\n", BLUE);
//
//	char	src[] = "0123456789";
//	char	dest1[100] = "abcdefghijklmnopqrstuvwxyz";
//	char	dest2[100] = "abcdefghijklmnopqrstuvwxyz";
//
//	int ret1 = ft_strlcat(dest1, src, strlen(dest1) + strlen(src) + 1);
//	int ret2 = strlcat(dest2, src, strlen(dest2) + strlen(src) + 1);
//	assert_str_equal("Check that ft_strlcat concats two strings correctly when destsize == dest_len + src_len + 1: ",
//					dest1, dest2);
//	assert_int_equal("Check that ft_strlcat returns the correct value: ", ret1, ret2);
//	
//	strcpy(dest1, "abcdefghijklmnopqrstuvwxyz");
//	strcpy(dest2, "abcdefghijklmnopqrstuvwxyz");
//	
//	ret1 = ft_strlcat(dest1, src, strlen(dest1) + 1);
//	ret2 = strlcat(dest2, src, strlen(dest2) + 1);
//
//	assert_str_equal("Check that ft_strlcat concats two strings correctly when destsize == dest_len + 1: ",
//					dest1, dest2);
//	assert_int_equal("Check that ft_strlcat returns the correct value: ", ret1, ret2);
//	
//	strcpy(dest1, "abcdefghijklmnopqrstuvwxyz");
//	strcpy(dest2, "abcdefghijklmnopqrstuvwxyz");
//	
//	ret1 = ft_strlcat(dest1, src, strlen(dest1));
//	ret2 = strlcat(dest2, src, strlen(dest2));
//
//	assert_str_equal("Check that ft_strlcat concats two strings correctly when destsize == dest_len: ",
//					dest1, dest2);
//	assert_int_equal("Check that ft_strlcat returns the correct value: ", ret1, ret2);
//
//
//	int i = 0;
//	bool test;
//	while (i < 10000)
//	{
//		strcpy(dest1, "abcdefghijklmnopqrstuvwxyz");
//		strcpy(dest2, "abcdefghijklmnopqrstuvwxyz");
//		ret1 = ft_strlcat(dest1, src, strlen(dest1));
//		ret2 = strlcat(dest2, src, strlen(dest2));
//		test = assert_str_equal("", dest1, dest2) && assert_int_equal("", ret1, ret2);
//		if (!test)
//			break;
//		i++;
//	}
//	assert_true("Testing dstsizes from 0 -> 10000: ", test);
//
//}
