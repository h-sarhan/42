/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:34:13 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 19:07:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
{
}

Contact::Contact(const std::string &firstName, const std::string &lastName,
				const std::string &nickName,const std::string &phoneNumber,
				const std::string &secret)
		:	firstName(firstName), lastName(lastName), nickName(nickName),
			phoneNumber(phoneNumber), secret(secret)
{}

Contact &Contact::operator=(const Contact &contact)
{
	this->firstName = contact.firstName;
	this->lastName = contact.lastName;
	this->nickName = contact.nickName;
	this->phoneNumber = contact.phoneNumber;
	this->secret = contact.secret;
	return (*this);
}
