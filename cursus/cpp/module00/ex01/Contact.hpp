/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:28:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 18:50:52 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT
# define CONTACT

# include <string>

class Contact
{
public:
	Contact();
	Contact(const std::string &firstName, const std::string &lastName,
			const std::string &nickName,const std::string &phoneNumber,
			const std::string &secret);
	Contact &operator=(const Contact &contact);
private:
	std::string	firstName;
	std::string	lastName;
	std::string	nickName;
	std::string	phoneNumber;
	std::string	secret;
};

#endif