#include "Bank.h"
#include <iostream>

Bank::Bank() {
}

bool Bank::registerUser(const std::string& name, const std::string& password) {
    for (const auto& user : users) {
        if (user->getName() == name) {
            std::cout << "用户已存在！" << std::endl;
            return false;
        }
    }
    users.push_back(new User(name, password));
    std::cout << "注册成功！" << std::endl;
    return true;
}

User* Bank::loginUser(const std::string& name, const std::string& password) {
    for (const auto& user : users) {
        if (user->getName() == name && user->verifyPassword(password)) {
            std::cout << "登陆成功！" << std::endl;
            return user;
        }
    }
    std::cout << "用户名或密码错误！" << std::endl;
    return nullptr;
}

void Bank::showUsers() const {
    for (const auto& user : users) {
        std::cout << "用户: " << user->getName() << std::endl;
    }
}
