#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "Date.h"

class Accumulator {
public:
    Accumulator(double rate);
    void change(double value, const Date& date);
    double accumulate(const Date& date) const;

private:
    double total;
    double rate;
    Date lastDate;
};

#endif // ACCUMULATOR_H
