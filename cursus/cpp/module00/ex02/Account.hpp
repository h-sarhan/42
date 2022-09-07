/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 05:49:12 by hsarhan           #+#    #+#             */
/*   Updated: 2022/09/07 06:12:40 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <ctime>
#include <iostream>
#include <iomanip>
class Account
{

public:
	typedef Account t;

	static int getNbAccounts(void);
	static int getTotalAmount(void);
	static int getNbDeposits(void);
	static int getNbWithdrawals(void);
	static void displayAccountsInfos(void);

	Account(int initial_deposit);
	~Account(void);

	void makeDeposit(int deposit);
	bool makeWithdrawal(int withdrawal);
	int checkAmount(void) const;
	void displayStatus(void) const;
	static void _displayTimestamp(void);

private:
	static int _nbAccounts;
	static int _totalAmount;
	static int _totalNbDeposits;
	static int _totalNbWithdrawals;


	int _accountIndex;
	int _amount;
	int _nbDeposits;
	int _nbWithdrawals;

	Account(void);
};

// ************************************************************************** //
// vim: set ts=4 sw=4 tw=80 noexpandtab:                                      //
// -*- indent-tabs-mode:t;                                                   -*-
// -*- mode: c++-mode;                                                       -*-
// -*- fill-column: 75; comment-column: 75;                                  -*-
// ************************************************************************** //

#endif /* __ACCOUNT_H__ */
