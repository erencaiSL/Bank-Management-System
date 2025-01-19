#include "SavingsAccount.h"
#include <iostream>
#include <sstream>
#include <iomanip>

SavingsAccount::SavingsAccount(const std::string& owner, const Date& date, bool isFixedTerm)
        : Account(owner, date), isFixedTerm(isFixedTerm), creationDate(date), lastSettlementDate(date) {
}

void SavingsAccount::deposit(double amount, const Date& date) {
    Account::deposit(amount, date);
}

void SavingsAccount::withdraw(double amount, const Date& date) {
    Account::withdraw(amount, date);
}

void SavingsAccount::settle(const Date& date) {
    int days = date - lastSettlementDate;
    if (isFixedTerm && days >= 365) {
        double interest = balance * 0.015; // 定期储蓄的年利率为1.5%
        balance += interest;
        lastSettlementDate = date;
    } else if (!isFixedTerm && date.getMonth() != lastSettlementDate.getMonth()) {
        double interest = balance * 0.01; // 活期储蓄的月利率为1%
        balance += interest;
        lastSettlementDate = date;
    }
    Account::settle(date);
}

void SavingsAccount::transfer(Account& to, double amount, const Date& date) {
    withdraw(amount, date);
    to.deposit(amount, date);
}

void SavingsAccount::show() const {
    std::cout << "账户ID: #" << id << " 账户名: " << name << ", 余额: " << balance << std::endl;
}
