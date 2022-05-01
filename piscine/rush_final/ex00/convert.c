/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 08:31:26 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/27 21:24:47 by mwasef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		power_of_10(int power);
char	*search_dictionary(int to_find_key, char *buffer);
int		get_num_digits_from_int(int num);
void	put_word(char *str, int add_space);

int	handle_tens(int tens, char *buffer, int *add_space)
{
	char	*value;
	int		skip_ones;

	skip_ones = 0;
	if (tens <= 20 && tens > 0)
	{
		value = search_dictionary(tens, buffer);
		put_word(value, *add_space);
		*add_space = 1;
		skip_ones = 1;
		free(value);
	}
	else if (tens > 20)
	{
		tens -= tens % 10;
		value = search_dictionary(tens, buffer);
		put_word(value, *add_space);
		*add_space = 1;
		free(value);
	}
	return (skip_ones);
}

void	convert_3_digits(int digits, char *buffer, int add_space)
{
	int		hundreds;
	int		skip_ones;
	int		ones;
	char	*value;

	hundreds = digits / 100;
	if (hundreds != 0)
	{
		value = search_dictionary(hundreds, buffer);
		put_word(value, add_space);
		add_space = 1;
		put_word(search_dictionary(100, buffer), add_space);
		free(value);
	}
	skip_ones = handle_tens(digits % 100, buffer, &add_space);
	ones = digits % 10;
	if (ones != 0 && !skip_ones)
	{
		value = search_dictionary(ones, buffer);
		put_word(value, add_space);
		free(value);
	}
}

int	get_num_places(int num)
{
	int	num_places;
	int	num_digits;

	num_places = 1;
	num_digits = get_num_digits_from_int(num);
	if (num_digits / 3 > 0 && num_digits % 3 != 0)
		num_places += num_digits / 3;
	else
		num_places += num_digits / 3 - 1;
	return (num_places);
}

void	print_place(int num, int current_place, char *buffer, int add_space)
{
	int		three_digits;
	char	*place_value;

	three_digits = num / power_of_10(3 * current_place);
	convert_3_digits(three_digits, buffer, add_space);
	add_space = 1;
	place_value = search_dictionary(power_of_10(3 * current_place), buffer);
	put_word(place_value, add_space);
	free(place_value);
}

void	convert(int num, char *buffer)
{
	int		add_space;
	int		current_place;
	char	*place_value;

	add_space = 0;
	if (num == 0)
	{
		place_value = search_dictionary(0, buffer);
		put_word(place_value, add_space);
		free(place_value);
		write(1, "\n", 1);
		return ;
	}
	current_place = get_num_places(num) - 1;
	add_space = 0;
	while (current_place > 0 && num != 0)
	{
		print_place(num, current_place, buffer, add_space);
		add_space = 1;
		num %= power_of_10(3 * current_place);
		current_place--;
	}
	convert_3_digits(num, buffer, add_space);
	write(1, "\n", 1);
}
