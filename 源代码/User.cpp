#include "User.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include <iostream>

User::User(const std::string& name, const std::string& password)
        : name(name), password(password) {
}

bool User::verifyPassword(const std::string& password) const {
    return this->password == password;
}

void User::addAccount(Account* account) {
    accounts.push_back(account);
    std::cout << "账户ID: #" << account->getAccountID() << " created balance: " << account->getBalance() << std::endl;
}

void User::addFinancialProduct(FinancialProduct* product) {
    financialProducts.push_back(product);
    std::cout << "Financial product added." << std::endl;
}

void User::showAccounts(const Date& currentDate) const {
    for (const auto& account : accounts) {
        account->show();
    }
    for (const auto& product : financialProducts) {
        product->show(currentDate);
    }
}

std::string User::getName() const {
    return name;
}

std::vector<Account*>& User::getAccounts() {
    return accounts;
}

std::vector<FinancialProduct*>& User::getFinancialProducts() {
    return financialProducts;
}

double User::getTotalBalance() const {
    double total = 0;
    for (const auto& account : accounts) {
        total += account->getBalance();
    }
    return total;
}

void User::settleFinancialProducts(const Date& currentDate) {
    for (auto& product : financialProducts) {
        if (product->monthsUntilMature(currentDate) <= 0) {
            double amountReceived = product->sell(currentDate);
            product->getAccount()->deposit(amountReceived, currentDate);
            std::cout << "Financial product matured and sold." << std::endl;
        }
    }
}

double User::calculateInterest(const Date& lastMonthDate, const Date& currentDate) {
    double totalInterest = 0;
    for (auto& account : accounts) {
        if (auto* savingsAccount = dynamic_cast<SavingsAccount*>(account)) {
            double balance = savingsAccount->getBalance();
            int days = currentDate - lastMonthDate;
            double interest = balance * 0.0001 * days;
            savingsAccount->deposit(interest, currentDate);
            totalInterest += interest;
        }
    }
    return totalInterest;
}

double User::calculateOverdueInterest(const Date& lastMonthDate, const Date& currentDate) {
    double totalOverdueInterest = 0;
    for (auto& account : accounts) {
        if (auto* creditAccount = dynamic_cast<CreditAccount*>(account)) {
            if (creditAccount->getBalance() > 0) {
                int days = currentDate - lastMonthDate;
                double overdueInterest = creditAccount->getBalance() * 0.0005 * days;
                totalOverdueInterest += overdueInterest;
            }
        }
    }
    return totalOverdueInterest;
}
