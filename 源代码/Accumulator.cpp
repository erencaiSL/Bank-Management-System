#include "Accumulator.h"

Accumulator::Accumulator(double rate) : total(0), rate(rate), lastDate(2023, 6, 1) {}


void Accumulator::change(double value, const Date& date) {
    total += value;
    lastDate = date;
}

double Accumulator::accumulate(const Date& date) const {
    int days = date - lastDate;
    return total * rate * days / 365;
}
