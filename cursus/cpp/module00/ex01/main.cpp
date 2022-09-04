/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:36:00 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 19:07:40 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <iostream>

void	addToPhoneBook(PhoneBook &phoneBook)
{
	std::string	first;
	std::string	last;
	std::string	nick;
	std::string	number;
	std::string	secret;

	std::cout << "Enter first name: " << std::endl;
	std::cin >> first;
	std::cout << "Enter last name: " << std::endl;
	std::cin >> last;
	std::cout << "Enter nickname: " << std::endl;
	std::cin >> nick;
	std::cout << "Enter phone number: " << std::endl;
	std::cin >> number;
	std::cout << "Enter secret: " << std::endl;
	std::cin >> secret;
	phoneBook.addContact(Contact(first, last, nick, number, secret));
}

int	main()
{
	std::string	command;
	PhoneBook	phoneBook;

	std::cout << "Enter a command" << std::endl;
	std::cout << "1. ADD" << std::endl << "2. SEARCH" << std::endl << "3. EXIT" << std::endl;
	std::cin >> command;
	while (command != "EXIT")
	{
		if (command == "ADD")
		{
			addToPhoneBook(phoneBook);
		}
		if (command == "DISPLAY")
		{

		}
		std::cout << "Enter a command" << std::endl;
		std::cout << "1. ADD" << std::endl << "2. SEARCH" << std::endl << "3. EXIT" << std::endl;
		std::cin >> command;
	}
}