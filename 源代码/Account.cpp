#include "Account.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int Account::accountCounter = 1;

Account::Account(const std::string& name, const Date& date)
        : name(name), lastDate(date), balance(0), accumulation(0) {
    std::ostringstream oss;
    oss << std::setw(5) << std::setfill('0') << accountCounter++;
    this->id = oss.str();
}

void Account::deposit(double amount, const Date& date) {
    calculateDailyInterest(date);
    balance += amount;
    lastDate = date;
}

void Account::withdraw(double amount, const Date& date) {
    calculateDailyInterest(date);
    balance -= amount;
    lastDate = date;
}

void Account::settle(const Date& date) {
    calculateDailyInterest(date);
    lastDate = date;
}

std::string Account::getAccountID() const {
    return id;
}

double Account::getBalance() const {
    return balance;
}

void Account::calculateDailyInterest(const Date& date) {
    int days = date - lastDate;
    double dailyInterestRate = 0.0001; // 0.01%

    for (int i = 0; i < days; ++i) {
        double interest = balance * dailyInterestRate;
        balance += interest;
    }

    lastDate = date;
}

void Account::show() const {
    std::cout << "账户ID: #" << id << " 账户名: " << name << ", 余额: " << balance << std::endl;
}
