#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "Account.h"
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "Date.h"
#include "FinancialProduct.h"
#include "User.h"
#include "Bank.h"

using namespace std;

void showMenu() {
    cout << "o: 开户（sa：储蓄账户，ca：信用账户），d: 存款，w: 取款，t: 转账，f: 购买/卖出理财产品，n: 进入下个月并打印账单，p: 打印所有账户信息，c: 改变当前日期，q: 退出程序" << endl;
}

void printTotalBalance(User* user, const Date& today) {
    cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " Total: " << user->getTotalBalance() << " command> ";
}

void printMonthlyStatement(User* user, const Date& lastMonthDate, const Date& currentDate) {
    cout << currentDate.getYear() << "-" << currentDate.getMonth() << "-1" << endl;
    cout << "这是您上个月的账户信息：" << endl;
    user->showAccounts(lastMonthDate);
    cout << "这是您上个月的账单：" << endl;

    double totalBalance = 0;
    double totalDebt = 0;

    for (const auto& account : user->getAccounts()) {
        if (dynamic_cast<SavingsAccount*>(account) != nullptr) {
            totalBalance += account->getBalance();
        } else if (auto* creditAccount = dynamic_cast<CreditAccount*>(account)) {
            totalDebt += creditAccount->getDebt();
        }
    }

    cout << "Balance：" << totalBalance << endl;
    cout << "Debt：" << totalDebt << endl;
    cout << "Total：" << (totalBalance - totalDebt) << endl;
}

int main() {
    Bank bank;
    Date today(2008, 11, 1);
    User* currentUser = nullptr;

    cout << "尊敬的用户您好， 欢迎使用个人银行账户管理系统。" << endl;
    cout << "你可以选择（1）注册（2）登陆（3）退出" << endl;

    while (true) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            string name, password;
            cout << "请输入你的用户名" << endl;
            cin >> name;
            cout << "请输入您的密码" << endl;
            cin >> password;
            bank.registerUser(name, password);
        } else if (choice == 2) {
            string name, password;
            cout << "请输入您的用户名" << endl;
            cin >> name;
            cout << "请输入您的密码" << endl;
            cin >> password;
            currentUser = bank.loginUser(name, password);
            if (currentUser) {
                break;
            }
        } else if (choice == 3) {
            return 0;
        }
        cout << "你可以选择（1）注册（2）登陆（3）退出" << endl;
    }

    cout << "您可以开始使用个人银行管理系统，请按下对应按键进行您想要的操作：" << endl;
    showMenu();

    char action;
    while (true) {
        printTotalBalance(currentUser, today);
        cin >> action;

        if (action == 'o') {
            string accountType;
            cout << "请选择账户类型(sa: 储蓄账户, ca: 信用账户): ";
            cin >> accountType;

            if (accountType == "sa") {
                char termType;
                cout << "请选择活期（c）还是定期（f）: ";
                cin >> termType;
                bool isFixedTerm = (termType == 'f');
                currentUser->addAccount(new SavingsAccount(currentUser->getName(), today, isFixedTerm));
                // 输出账户信息
                cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " #"
                     << currentUser->getAccounts().back()->getAccountID() << " created balance: " << currentUser->getAccounts().back()->getBalance() << endl;
            } else if (accountType == "ca") {
                currentUser->addAccount(new CreditAccount(currentUser->getName(), today));
                // 输出账户信息
                cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " #"
                     << currentUser->getAccounts().back()->getAccountID() << " Debt: 0 Available credit: 10000" << endl;
            }
        } else if (action == 'd') {
            string accountID;
            double amount;
            cout << "请输入账户ID: ";
            cin >> accountID;
            cout << "请输入存款金额: ";
            cin >> amount;
            int id;
            try {
                id = stoi(accountID) - 1;
            } catch (const std::invalid_argument& e) {
                cout << "无效的账户ID" << endl;
                continue;
            } catch (const std::out_of_range& e) {
                cout << "账户ID超出范围" << endl;
                continue;
            }
            if (id < 0 || id >= currentUser->getAccounts().size()) {
                cout << "无效的账户ID" << endl;
                continue;
            }
            currentUser->getAccounts()[id]->deposit(amount, today);
            cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " #"
                 << currentUser->getAccounts()[id]->getAccountID() << " + " << amount << " " << currentUser->getAccounts()[id]->getBalance() << endl;
        } else if (action == 'w') {
            string accountID;
            double amount;
            cout << "请输入账户ID: ";
            cin >> accountID;
            cout << "请输入取款金额: ";
            cin >> amount;
            int id;
            try {
                id = stoi(accountID) - 1;
            } catch (const std::invalid_argument& e) {
                cout << "无效的账户ID" << endl;
                continue;
            } catch (const std::out_of_range& e) {
                cout << "账户ID超出范围" << endl;
                continue;
            }
            if (id < 0 || id >= currentUser->getAccounts().size()) {
                cout << "无效的账户ID" << endl;
                continue;
            }
            currentUser->getAccounts()[id]->withdraw(amount, today);
            cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " #"
                 << currentUser->getAccounts()[id]->getAccountID() << " - " << amount << " " << currentUser->getAccounts()[id]->getBalance() << endl;
        } else if (action == 't') {
            string fromAccountID, toAccountID;
            double amount;
            cout << "请输入转出账户ID: ";
            cin >> fromAccountID;
            cout << "请输入转入账户ID: ";
            cin >> toAccountID;
            cout << "请输入转账金额: ";
            cin >> amount;
            int fromID, toID;
            try {
                fromID = stoi(fromAccountID) - 1;
                toID = stoi(toAccountID) - 1;
            } catch (const std::invalid_argument& e) {
                cout << "无效的账户ID" << endl;
                continue;
            } catch (const std::out_of_range& e) {
                cout << "账户ID超出范围" << endl;
                continue;
            }
            if (fromID < 0 || fromID >= currentUser->getAccounts().size() ||
                toID < 0 || toID >= currentUser->getAccounts().size()) {
                cout << "无效的账户ID" << endl;
                continue;
            }
            currentUser->getAccounts()[fromID]->transfer(*currentUser->getAccounts()[toID], amount, today);
        } else if (action == 'f') {
            string accountID;
            cout << "请输入账户ID: ";
            cin >> accountID;
            string operation;
            cout << "你需要买入（buy）或是卖出（sell）: ";
            cin >> operation;
            int id;
            try {
                id = stoi(accountID) - 1;
            } catch (const std::invalid_argument& e) {
                cout << "无效的账户ID" << endl;
                continue;
            } catch (const std::out_of_range& e) {
                cout << "账户ID超出范围" << endl;
                continue;
            }
            if (id < 0 || id >= currentUser->getAccounts().size()) {
                cout << "无效的账户ID" << endl;
                continue;
            }
            if (operation == "buy") {
                double amount;
                int duration;
                cout << "请输入你要购买的数量: ";
                cin >> amount;
                cout << "请输入你需要持有的期限（以月为单位）: ";
                cin >> duration;
                currentUser->getAccounts()[id]->withdraw(amount, today); // 从账户中扣除购买理财产品的金额
                currentUser->addFinancialProduct(new FinancialProduct(currentUser->getAccounts()[id], amount, 0.06, today, duration));
                // 输出购买理财产品后的账户信息
                cout << "Financial product added." << endl;
                cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " #"
                     << currentUser->getAccounts()[id]->getAccountID() << " Debt: " << currentUser->getAccounts()[id]->getBalance()
                     << " Available credit: " << currentUser->getAccounts()[id]->getBalance() + amount
                     << " Financial Product: " << amount << " Distance from the due date: " << duration << " months 0 days" << endl;
            } else if (operation == "sell") {
                double amountReceived = currentUser->getFinancialProducts()[id]->sell(today);
                currentUser->getFinancialProducts()[id]->getAccount()->deposit(amountReceived, today);
                // 输出卖出理财产品后的账户信息
                cout << "Financial product sold." << endl;
                cout << today.getYear() << "-" << today.getMonth() << "-" << today.getDay() << " #"
                     << currentUser->getFinancialProducts()[id]->getAccount()->getAccountID() << " Debt: "
                     << currentUser->getFinancialProducts()[id]->getAccount()->getBalance()
                     << " Available credit: " << currentUser->getFinancialProducts()[id]->getAccount()->getBalance()
                     << " Financial Product: " << amountReceived << " Distance from the due date: 0 months 0 days" << endl;
            }
        } else if (action == 'n') {
            // 进入下个月并结算
            Date lastMonthDate = today;
            currentUser->settleFinancialProducts(today); // 结算所有金融产品
            for (auto& account : currentUser->getAccounts()) {
                if (auto* creditAccount = dynamic_cast<CreditAccount*>(account)) {
                    creditAccount->settle(today); // 结算信用账户的利息
                }
            }
            today.addDays(30 - today.getDay() + 1); // 跳到下个月的1号
            printMonthlyStatement(currentUser, lastMonthDate, today);
        } else if (action == 'p') {
            currentUser->showAccounts(today);
        } else if (action == 'c') {
            int days;
            cout << "请输入要增加的天数: ";
            cin >> days;
            today.addDays(days);
            for (auto& account : currentUser->getAccounts()) {
                account->calculateDailyInterest(today);
            }
        } else if (action == 'q') {
            break;
        }
    }

    return 0;
}
