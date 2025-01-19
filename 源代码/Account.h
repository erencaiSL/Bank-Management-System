#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "Date.h"

class Account {
public:
    Account(const std::string& name, const Date& date);
    virtual void deposit(double amount, const Date& date);
    virtual void withdraw(double amount, const Date& date);
    virtual void settle(const Date& date);
    virtual void show() const = 0;
    std::string getAccountID() const;
    double getBalance() const;
    virtual void transfer(Account& to, double amount, const Date& date) = 0;

    void calculateDailyInterest(const Date& date);

protected:
    static int accountCounter;
    std::string id;
    std::string name;
    Date lastDate;
    double balance;
    double accumulation;
};

#endif // ACCOUNT_H
