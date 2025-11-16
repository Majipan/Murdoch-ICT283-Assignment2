#include "Time.h"
#include <iostream>
#include <string>

using namespace std;

/** Main Constructor */
Time::Time() : hour(""), mins("") {}

/** Constructor Overload */
Time::Time(string h, string m) : hour(h), mins(m) {}

/// =================================================================================

/** Getter for time formatted */
const string Time::getTime() const {
    return hour+":"+mins;
}

/// =================================================================================

/** Setter for Hour */
void Time::setHour(string h) { hour = h; }
/** Setter for Minute */
void Time::setMins(string m) { mins = m; }

/// =================================================================================

/** Operator Override for < */
bool Time::operator<(const Time& other) const {
    int h1 = std::stoi(hour);
    int h2 = std::stoi(other.hour);
    if (h1 != h2) return h1 < h2;

    int m1 = std::stoi(mins);
    int m2 = std::stoi(other.mins);
    return m1 < m2;
}
/** Operator Override for == */
bool Time::operator==(const Time& other) const {
    return hour == other.hour && mins == other.mins;
}
