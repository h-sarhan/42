/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:47:20 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 19:00:57 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
	: contacts_idx(0)
{
}

void	PhoneBook::addContact(const Contact &contact)
{
	contacts[contacts_idx] = contact;
	contacts_idx++;
	if (contacts_idx == 8)
		contacts_idx = 0;
}

void	PhoneBook::displayContacts() const
{
	
}

void	PhoneBook::displayContact(const size_t contact_idx) const
{
	(void)contact_idx;
}