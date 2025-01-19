#include "Date.h"
#include <iostream>

Date::Date(int year, int month, int day)
        : year(year), month(month), day(day) {
}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

void Date::show() const {
    std::cout << year << "-" << month << "-" << day;
}

int Date::operator-(const Date& other) const {
    // 简单计算日期差
    return (year - other.year) * 365 + (month - other.month) * 30 + (day - other.day);
}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int year, int month) const {
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysInMonth[month - 1];
}

void Date::addDays(int days) {
    day += days;
    while (day > daysInMonth(year, month)) {
        day -= daysInMonth(year, month);
        month += 1;
        if (month > 12) {
            month = 1;
            year += 1;
        }
    }
}
