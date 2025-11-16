#include "date.h"
#include <iostream>

using namespace std;

/** Constructor */
Date::Date() : day(1), month(1), year(1970){}

/** Constructor Overload */
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

/// =================================================================================

/** Getter for day */
const int Date::getDay() const { return day; }
/** Getter for month */
const int Date::getMonth() const { return month; }
/** Getter for year */
const int Date::getYear() const { return year; }

/// =================================================================================

/** Setter for day */
void Date::setDay(int d) {
    day = d;
}
/** Setter for month */
void Date::setMonth(int m) {
    month = m;
}
/** Setter for year */
void Date::setYear(int y) {
    year = y;
}

/// =================================================================================

/** Operator Override < */
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}
/** Operator Override == */
bool Date::operator==(const Date& other) const {
    return day == other.day &&
           month == other.month &&
           year == other.year;
}
