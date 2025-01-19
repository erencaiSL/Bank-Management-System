#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

#include "Account.h"

class CreditAccount : public Account {
public:
    CreditAccount(const std::string& owner, const Date& date);
    void deposit(double amount, const Date& date) override;
    void withdraw(double amount, const Date& date) override;
    void settle(const Date& date) override;
    void transfer(Account& to, double amount, const Date& date) override;
    void show() const override;
    double getDebt() const; // 添加 getDebt 方法的声明

private:
    double annualFee;
    double dailyWithdrawalInterest;
    double overdueInterestRate;
    double debt;
    double availableCredit;
    Date lastDateCheckedForDebt;
};

#endif // CREDITACCOUNT_H
