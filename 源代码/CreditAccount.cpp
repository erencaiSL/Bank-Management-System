#include "CreditAccount.h"
#include <iostream>
#include <sstream>
#include <iomanip>

CreditAccount::CreditAccount(const std::string& owner, const Date& date)
        : Account(owner, date), annualFee(50), dailyWithdrawalInterest(0.0005),
          overdueInterestRate(0.0005), debt(0), availableCredit(10000), lastDateCheckedForDebt(date) {
}

void CreditAccount::deposit(double amount, const Date& date) {
    Account::deposit(amount, date);
    if (debt > 0) {
        double repayment = std::min(amount, debt);
        debt -= repayment;
        availableCredit += repayment;
    }
}

void CreditAccount::withdraw(double amount, const Date& date) {
    if (amount > availableCredit) {
        std::cout << "可用额度不足，无法取款。" << std::endl;
        return;
    }
    Account::withdraw(amount, date);
    debt += amount;
    availableCredit -= amount;
}

void CreditAccount::settle(const Date& date) {
    int days = date - lastDateCheckedForDebt;
    if (debt > 0 && days > 0) {
        double interest = debt * overdueInterestRate * days;
        debt += interest;
    }
    lastDateCheckedForDebt = date;
    Account::settle(date);
}

void CreditAccount::transfer(Account& to, double amount, const Date& date) {
    if (amount > availableCredit) {
        std::cout << "可用额度不足，无法转账。" << std::endl;
        return;
    }
    withdraw(amount, date);
    to.deposit(amount, date);
}

void CreditAccount::show() const {
    std::cout << "账户ID: #" << id << " Debt: " << debt << " Available credit: " << availableCredit << std::endl;
}

double CreditAccount::getDebt() const {
    return debt;
}
