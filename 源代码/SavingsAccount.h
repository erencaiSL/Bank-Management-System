#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& owner, const Date& date, bool isFixedTerm);
    void deposit(double amount, const Date& date) override;
    void withdraw(double amount, const Date& date) override;
    void settle(const Date& date) override;
    void transfer(Account& to, double amount, const Date& date) override; // 添加这一行
    void show() const override;

private:
    bool isFixedTerm;
    Date creationDate;  // 添加这一行
    Date lastSettlementDate;  // 添加这一行
};

#endif // SAVINGSACCOUNT_H
