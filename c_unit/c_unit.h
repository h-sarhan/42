/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_unit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:42:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/02 11:53:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_UNIT_H
# define C_UNIT_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define SUCCESS "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE  "\x1b[36m"
# define ERROR "\x1b[31m"
# define RESET "\x1b[0m"
# define WHITE "\x1b[0m"

# define CHECKMARK "\xE2\x9C\x93"
# define CROSS "\u2717"

// assert_int.c
void	assert_int_equal(char *msg, int result, int expected);
void	assert_int_array_equal(char *msg, int *result, int *expected, int len);
void	assert_int_array_is_sorted(char *msg, int *arr, int arr_len);

// assert_string.c
void	assert_char_equal(char *msg, char result, char expected);
void	assert_str_equal(char *msg, char *result, char *expected);
void	assert_str_array_equal(char *msg, char **res, char **expected, int len);
void	assert_str_array_is_sorted(char *msg, char **arr, int arr_len);

// assert_null.c
void	assert_is_not_null(char *msg, void *result);
void	assert_is_null(char *msg, void *result);

// test_utils.c
void	print_int_array(int *arr, int arr_len, char *color);
void	print_msg_color(char *msg, char *color);
void	print_str_array(char **arr, int arr_len, char *color);
void	ft_putnbr(int nb, char *color);
int		ft_strcmp(char *s1, char *s2);

// assert_bool.c
void	assert_true(char *msg, int result);
void	assert_false(char *msg, int result);
#endif
