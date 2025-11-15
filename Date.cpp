#include "date.h"
#include <iostream>

using namespace std;

/** Constructor */
Date::Date() : day(1), month(1), year(1970){}

/** Constructor Overload */
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

/** Getter for day */
int Date::getDay() const { return day; }
/** Getter for month */
int Date::getMonth() const { return month; }
/** Getter for year */
int Date::getYear() const { return year; }

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
