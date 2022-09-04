/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:25:24 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/04 18:47:50 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK
# define PHONE_BOOK

#include "Contact.hpp"

class PhoneBook
{
public:
	PhoneBook();
	void	addContact(const Contact &contact);
	void	displayContacts() const;
	void	displayContact(const size_t contact_idx) const;
private:
	Contact	contacts[8];
	size_t	contacts_idx;
};
#endif