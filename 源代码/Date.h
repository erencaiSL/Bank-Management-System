#ifndef DATE_H
#define DATE_H

class Date {
public:
    Date(int year, int month, int day);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    void show() const;
    int operator-(const Date& other) const;
    void addDays(int days);

private:
    int year;
    int month;
    int day;
    bool isLeapYear(int year) const;
    int daysInMonth(int year, int month) const;
};

#endif // DATE_H
