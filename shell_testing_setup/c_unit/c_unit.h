/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_unit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:42:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/04 22:52:38 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_UNIT_H
# define C_UNIT_H

# include <unistd.h>
# include <stdbool.h>

// Colors
# define SUCCESS "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE  "\x1b[36m"
# define ERROR "\x1b[31m"
# define RESET "\x1b[0m"
# define WHITE "\x1b[0m"

// Symbols
# define CHECKMARK "\xE2\x9C\x93"
# define CROSS "\u2717"

// assert_int.c
bool	assert_int_equal(char *msg, int result, int expected);
bool	assert_int_array_equal(char *msg, int *result, int *expected, int len);
bool	assert_int_array_is_sorted(char *msg, int *arr, int arr_len);

// assert_string.c
bool	assert_char_equal(char *msg, char result, char expected);
bool	assert_str_equal(char *msg, char *result, char *expected);
bool	assert_str_array_equal(char *msg, char **res, char **expected, int len);
bool	assert_str_array_is_sorted(char *msg, char **arr, int arr_len);

// assert_null.c
bool	assert_is_not_null(char *msg, void *result);
bool	assert_is_null(char *msg, void *result);

// assert_bool.c
bool	assert_true(char *msg, bool result);
bool	assert_false(char *msg, bool result);
bool	assert_bool_array_equal(char *msg, bool *res, bool *expected, int len);

// test_utils.c
void	print_int_array(int *arr, int arr_len, char *color);
void	print_msg_color(char *msg, char *color);
void	print_str_array(char **arr, int arr_len, char *color);
void	print_bool_array(bool *arr, int arr_len, char *color);

// test_utils_2.c
void	test_util_putnbr(int nb, char *color);
int		test_util_strcmp(char *s1, char *s2);
#endif
