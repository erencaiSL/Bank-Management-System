#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account {
public:
    CheckingAccount(const std::string& owner, const Date& date);
    void deposit(double amount, const Date& date) override;
    void withdraw(double amount, const Date& date) override;
    void settle(const Date& date) override;
    void transfer(Account& to, double amount, const Date& date) override;
    void show() const override;
};

#endif // CHECKINGACCOUNT_H
