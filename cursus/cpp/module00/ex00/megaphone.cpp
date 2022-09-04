/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 00:53:31 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 01:01:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else
	{
		for (int arg_idx = 1; arg_idx < argc; arg_idx++)
		{
			char *arg = argv[arg_idx];
			for (size_t i = 0; i < std::strlen(arg); i++)
			{
				std::cout << staticstd::toupper(arg[i]);
			}
			std::cout << std::endl;
		}
	}
}