#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include "User.h"
#include "Account.h"
#include "Date.h"

class Bank {
public:
    Bank();
    bool registerUser(const std::string& name, const std::string& password);
    User* loginUser(const std::string& name, const std::string& password);
    void showUsers() const;

private:
    std::vector<User*> users;
};

#endif // BANK_H
