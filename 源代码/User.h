#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Account.h"
#include "FinancialProduct.h"

class User {
public:
    User(const std::string& name, const std::string& password);
    bool verifyPassword(const std::string& password) const;
    void addAccount(Account* account);
    void addFinancialProduct(FinancialProduct* product);
    void showAccounts(const Date& currentDate) const;
    void settleFinancialProducts(const Date& currentDate);
    std::string getName() const;
    std::vector<Account*>& getAccounts();
    std::vector<FinancialProduct*>& getFinancialProducts();
    double getTotalBalance() const;
    double calculateInterest(const Date& lastMonthDate, const Date& currentDate);
    double calculateOverdueInterest(const Date& lastMonthDate, const Date& currentDate);

private:
    std::string name;
    std::string password;
    std::vector<Account*> accounts;
    std::vector<FinancialProduct*> financialProducts;
};

#endif // USER_H
