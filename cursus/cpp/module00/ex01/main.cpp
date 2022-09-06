/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:36:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/07 02:07:05 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iostream>

int main(void)
{
	std::string command;
	PhoneBook phoneBook;

	std::cout << "Enter a command" << std::endl;
	std::cout << "1. ADD" << std::endl
			  << "2. SEARCH" << std::endl
			  << "3. EXIT" << std::endl;
	std::cin >> command;
	while (command != "EXIT" && std::cin)
	{
		if (command == "ADD")
		{
			phoneBook.addContact();
		}
		if (command == "SEARCH")
		{
			phoneBook.searchPhoneBook();
		}
		std::cout << "Enter a command" << std::endl;
		std::cout << "1. ADD" << std::endl
				  << "2. SEARCH" << std::endl
				  << "3. EXIT" << std::endl;
		std::cin >> command;
	}
}
