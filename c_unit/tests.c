/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 15:06:28 by hsarhan           #+#    #+#             */
/*   Updated: 2022/05/07 00:59:24 by hsarhan          ###   ########.fr       */
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
	assert_str_array_equal("This should pass: ", result, expected, 4);
	result[0] = "no";
	assert_str_array_equal("This should fail: ", result, expected, 4);
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

void	test_return_values()
{
	print_msg_color("\n---Testing assert methods return correct values---\n", BLUE);
	
	bool	trues[11];
	bool	falses[11];
	bool	expected_trues[11];
	bool	expected_falses[11];
	int		i;

	i = 0;
	while (i < 11)
		expected_trues[i++] = true;
	
	i = 0;
	while (i < 11)
		expected_falses[i++] = false;


	trues[0] = assert_int_equal("This should pass: ", 10, 10);
	falses[0] = assert_int_equal("This should fail: ", 10, 11);
	
	int	nums[2] = {1, 2};
	int	nums2[2] = {3, 1};
	
	trues[1] = assert_int_array_equal("This should pass: ", nums, nums, 2);
	falses[1] = assert_int_array_equal("This should fail: ", nums, nums2, 2);
	
	trues[2] = 	assert_int_array_is_sorted("This should pass: ", nums, 2);
	falses[2] =	assert_int_array_is_sorted("This should fail: ", nums2, 2);

	trues[3] = assert_char_equal("This should pass: ", 'a', 'a');
	falses[3] = assert_char_equal("This should fail: ", 'a', 'b');
	
	trues[4] = assert_str_equal("This should pass: ", "abc", "abc");
	falses[4] = assert_str_equal("This should fail: ", "abc", "ab");

	char	*words[2] = {"ab", "bc"};
	char	*words2[2] = {"zy", "bc"};

	trues[5] = assert_str_array_equal("This should pass: ", words, words, 2);
	falses[5] =assert_str_array_equal("This should fail: ", words, words2, 2);

	trues[6] = assert_str_array_is_sorted("This should pass: ", words, 2);
	falses[6] = assert_str_array_is_sorted("This should fail: ", words2, 2);

	int	num = 4;
	int	*num_ptr = &num;
	int	*this_is_null = NULL;

	trues[7] = assert_is_not_null("This should pass: ", num_ptr);
	falses[7] = assert_is_not_null("This should fail: ", this_is_null);
	
	trues[8] = assert_is_null("This should pass: ", this_is_null);
	falses[8] = assert_is_null("This should fail: ", num_ptr);

	trues[9] = assert_true("This should pass: ", true);
	falses[9] = assert_true("This should fail: ", false);

	trues[10] = assert_false("This should pass: ", false);
	falses[10] = assert_false("This should fail: ", true);
	assert_bool_array_equal("All true return values are correct: ",
			trues, expected_trues, 11);
	assert_bool_array_equal("All false return values are correct: ",
			falses, expected_falses, 11);
}

void	test_strs_to_ints()
{
	print_msg_color("\n---Testing assert atrs_to_ints---\n", BLUE);
	
	char	example_1[] = "[1, 2, 3]";
	int		expected_1[] = {1, 2, 3};
	int		expected_size_1 = 3;
	int		size;
	int		*res_1 = str_to_ints(example_1, &size);
	
	assert_int_array_equal("Test array of single digits in brackets: ",
			res_1, expected_1, expected_size_1);
	assert_int_equal("Test that size is correct: ", size, expected_size_1);
	
	char	example_2[] = "2, 2, 3";
	int		expected_2[] = {2, 2, 3};
	int		expected_size_2 = 3;
	int		*res_2 = str_to_ints(example_2, &size);
	
	assert_int_array_equal("Test array of single digits without brackets: ",
			res_2, expected_2, expected_size_2);
	assert_int_equal("Test that size is correct: ", size, expected_size_2);

	char	example_3[] = "132133, 19813, 1763";
	int		expected_3[] = {132133, 19813, 1763};
	int		expected_size_3 = 3;
	int		*res_3 = str_to_ints(example_3, &size);
	
	assert_int_array_equal("Test array of big numbers without brackets: ",
			res_3, expected_3, expected_size_3);
	assert_int_equal("Test that size is correct: ", size, expected_size_3);
	
	char	example_4[] = "-132133, 19813, -1763";
	int		expected_4[] = {-132133, 19813, -1763};
	int		expected_size_4 = 3;
	int		*res_4 = str_to_ints(example_4, &size);
	
	assert_int_array_equal("Test array of big negative numbers without brackets: ",
			res_4, expected_4, expected_size_4);
	assert_int_equal("Test that size is correct: ", size, expected_size_4);
	
	char	example_5[] = "[-132133, 19813, -1763]";
	int		expected_5[] = {-132133, 19813, -1763};
	int		expected_size_5 = 3;
	int		*res_5 = str_to_ints(example_5, &size);
	
	assert_int_array_equal("Test array of big negative numbers in brackets: ",
			res_5, expected_5, expected_size_5);
	assert_int_equal("Test that size is correct: ", size, expected_size_5);
	
	char	example_6[] = "[-132133]";
	int		expected_6[] = {-132133};
	int		expected_size_6 = 1;
	int		*res_6 = str_to_ints(example_6, &size);
	
	assert_int_array_equal("Test array of single big negative integer: ",
			res_6, expected_6, expected_size_6);
	assert_int_equal("Test that size is correct: ", size, expected_size_6);
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
	test_return_values();
	test_strs_to_ints();
}
*/

int	main(void)
{
	print_msg_color("Uncomment the tests :)\n", BLUE);
}
