#ifndef FINANCIALPRODUCT_H
#define FINANCIALPRODUCT_H

#include "Date.h"
#include "Account.h"

class FinancialProduct {
public:
    FinancialProduct(Account* account, double amount, double annualInterestRate, const Date& purchaseDate, int durationInMonths);
    void settle(const Date& currentDate);
    void show(const Date& currentDate) const;
    double sell(const Date& currentDate) const;
    int monthsUntilMature(const Date& currentDate) const;
    int daysUntilMature(const Date& currentDate) const;
    Account* getAccount() const; // 添加这一行

private:
    Account* account;
    double amount;
    double annualInterestRate;
    Date purchaseDate;
    int durationInMonths;
    bool isMature;
};

#endif // FINANCIALPRODUCT_H
