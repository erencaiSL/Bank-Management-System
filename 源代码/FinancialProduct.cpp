#include "FinancialProduct.h"
#include <iostream>

FinancialProduct::FinancialProduct(Account* account, double amount, double annualInterestRate, const Date& purchaseDate, int durationInMonths)
        : account(account), amount(amount), annualInterestRate(annualInterestRate), purchaseDate(purchaseDate), durationInMonths(durationInMonths), isMature(false) {
}

void FinancialProduct::settle(const Date& currentDate) {
    int daysHeld = currentDate - purchaseDate;
    int monthsHeld = daysHeld / 30;

    if (monthsHeld >= durationInMonths) {
        isMature = true;
        account->deposit(amount + (amount * annualInterestRate * (durationInMonths / 12.0)), currentDate);
    } else {
        account->deposit(amount + (amount * annualInterestRate * (monthsHeld / 12.0)), currentDate);
    }
}

double FinancialProduct::sell(const Date& currentDate) const {
    int daysHeld = currentDate - purchaseDate;
    int monthsHeld = daysHeld / 30;

    double rateAdjustment = (durationInMonths - monthsHeld) * 0.001;
    double adjustedInterestRate = annualInterestRate - rateAdjustment;
    if (adjustedInterestRate < 0) {
        adjustedInterestRate = 0; // 防止利率变成负值
    }

    return amount + (amount * adjustedInterestRate * (monthsHeld / 12.0));
}

int FinancialProduct::monthsUntilMature(const Date& currentDate) const {
    int daysHeld = currentDate - purchaseDate;
    int monthsHeld = daysHeld / 30;
    return durationInMonths - monthsHeld - 1;
}

int FinancialProduct::daysUntilMature(const Date& currentDate) const {
    int daysHeld = currentDate - purchaseDate;
    return (durationInMonths * 30 - daysHeld) % 30;
}

Account* FinancialProduct::getAccount() const {
    return account;
}

void FinancialProduct::show(const Date& currentDate) const {
    std::cout << "理财产品金额: " << amount << ", 年化利率: " << annualInterestRate * 100 << "%, 购买日期: ";
    purchaseDate.show();
    std::cout << ", 期限: " << durationInMonths << "个月, "
              << (isMature ? "已到期" : "未到期")
              << ", 距离到期: " << monthsUntilMature(currentDate) << "个月 "
              << daysUntilMature(currentDate) << "天" << std::endl;
}
