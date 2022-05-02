/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:06:28 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/02 11:54:08 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_unit.h"
/*
void	test_print_msg_color()
{
	print_msg_color("\n---Testing print_msg_color---\n", BLUE);

	print_msg_color("This is green\n", SUCCESS);
	print_msg_color("This is blue\n", BLUE);
	print_msg_color("This is red\n", ERROR);
	print_msg_color("This is yellow\n", YELLOW);
	print_msg_color("This is white\n", WHITE);
	print_msg_color(CHECKMARK " GREEN CHECK MARK!\n", SUCCESS);
	print_msg_color(CROSS " RED CROSS!\n", ERROR);
}


void	test_print_int_array()
{	
	print_msg_color("\n---Testing print_int_array---\n", BLUE);
	
	int	nums[5] = {1, 2, 3, 4, -58768};
	print_int_array(nums, 5, WHITE);
}

void	test_assert_int_equal()
{	
	print_msg_color("\n---Testing assert_int_equal---\n", BLUE);

	int	result = 10;
	int expected = 10;
	assert_int_equal("This should pass: ", result, expected);
	assert_int_equal("This should fail: ", result + 1, expected);
}

void	test_assert_int_array_equal()
{
	print_msg_color("\n---testing assert_int_array_equal---\n", BLUE);
	int	result[5] = {1, 2, 3, 4, 5};
	int	expected[5] = {1, 2, 3, 4, 5};
	assert_int_array_equal("this should pass: ", result, expected, 5);
	result[0] += 1;
	assert_int_array_equal("this should fail: ", result, expected, 5);
}

void test_assert_int_array_is_sorted()
{
	print_msg_color("\n---Testing assert_int_array_is_sorted---\n", BLUE);
	int	sorted_arr[5] = {1, 2, 3, 4, 5}; 
	int	unsorted_arr[5] = {1, 12, 3, 4, 5}; 
	assert_int_array_is_sorted("This should pass: ", sorted_arr, 5);
	assert_int_array_is_sorted("This should fail: ", unsorted_arr, 5);
}

void	test_assert_is_null()
{
	print_msg_color("\n---Testing assert_is_null---\n", BLUE);
	assert_is_null("This should pass: ", NULL);
	int lol = 1;
	assert_is_null("This should fail: ", &lol);
}

void	test_assert_is_not_null()
{
	print_msg_color("\n---Testing assert_is_not_null---\n", BLUE);
	int lol = 1;
	assert_is_not_null("This should pass: ", &lol);
	assert_is_not_null("This should fail: ", NULL);
}

void	test_assert_str_equal()
{
	print_msg_color("\n---Testing assert_string_equal---\n", BLUE);
	assert_str_equal("This should pass: ", "yo", "yo");
	assert_str_equal("This should fail: ", "hey", "yo");
	assert_str_equal("This should fail: ", "hey", "heyo");
}

void	test_assert_char_equal()
{
	print_msg_color("\n---Testing assert_char_equal---\n", BLUE);
	assert_char_equal("This should pass: ", 'y', 'y');
	assert_char_equal("This should fail: ", 'y', 'a');
}

void	test_assert_str_array_equal()
{
	print_msg_color("\n---Testing assert_str_array_equal---\n", BLUE);
	
	char	*result[4] = {"yo", "what is up", "cool", "swag"};
	char	*expected[4] = {"yo", "what is up", "cool", "swag"};
	assert_str_array_equal("this should pass: ", result, expected, 4);
	result[0] = "no";
	assert_str_array_equal("this should fail: ", result, expected, 4);
}

void	test_assert_str_array_is_sorted()
{
	print_msg_color("\n---Testing assert_str_array_is_sorted---\n", BLUE);
	char *sorted_arr[5] = {"a", "b", "c", "d", "d"}; 
	char *unsorted_arr[5] = {"a", "b", "c", "d", "a"};
	assert_str_array_is_sorted("This should pass: ", sorted_arr, 5);
	assert_str_array_is_sorted("This should fail: ", unsorted_arr, 5);
}

void	test_assert_true()
{
	print_msg_color("\n---Testing assert_true---\n", BLUE);
	assert_true("This should pass: ", 'a' == 'a');
	assert_true("This should fail: ", 'a' != 'a');
}

void	test_assert_false()
{
	print_msg_color("\n---Testing assert_false---\n", BLUE);
	assert_false("This should pass: ", 'a' != 'a');
	assert_false("This should fail: ", 'a' == 'a');
}

int main(void)
{
	test_print_msg_color();
	test_print_int_array();
	test_assert_int_equal();
	test_assert_int_array_equal();
	test_assert_int_array_is_sorted();
	test_assert_is_null();
	test_assert_is_not_null();
	test_assert_str_equal();
	test_assert_char_equal();
	test_assert_str_array_equal();
	test_assert_str_array_is_sorted();
	test_assert_true();
	test_assert_false();
}
*/
int	main(void)
{
	print_msg_color("Uncomment the tests :)\n", BLUE);
}
