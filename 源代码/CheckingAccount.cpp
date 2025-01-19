#include "CheckingAccount.h"
#include <iostream>
#include <sstream>
#include <iomanip>

CheckingAccount::CheckingAccount(const std::string& owner, const Date& date)
        : Account(owner, date) { // 只传递两个参数
    std::ostringstream oss;
    oss << std::setw(5) << std::setfill('0') << accountCounter++;
    this->id = oss.str();
}

void CheckingAccount::deposit(double amount, const Date& date) {
    Account::deposit(amount, date);
}

void CheckingAccount::withdraw(double amount, const Date& date) {
    Account::withdraw(amount, date);
}

void CheckingAccount::settle(const Date& date) {
    Account::settle(date);
}

void CheckingAccount::transfer(Account& to, double amount, const Date& date) {
    withdraw(amount, date);
    to.deposit(amount, date);
}

void CheckingAccount::show() const {
    std::cout << "账户ID: #" << id << " 账户名: " << name << ", 余额: " << balance << std::endl;
}
