#include "Time.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

/** Main Constructor */
Time::Time() : hour(0), mins(0) {}

/** Constructor Overload */
Time::Time(int h, int m) : hour(h), mins(m) {}

/// =================================================================================

/** Getter for time formatted */
const string Time::getTime() const {
    std::ostringstream os;
    os << std::setfill('0')
       << std::setw(2) << hour
       << ':'
       << std::setw(2) << mins;
    return os.str();
}

/** Getter for Hour unformatted */
const int Time::getHour() const {
    return hour;
}
/** Getter for Mins unformatted */
const int Time::getMins() const {
    return mins;
}

/// =================================================================================

/** Setter for Hour */
void Time::setHour(int h) { hour = h; }
/** Setter for Minute */
void Time::setMins(int m) { mins = m; }

/// =================================================================================

/** Operator Override for < */
bool Time::operator<(const Time& other) const {
    if (hour != other.hour) return hour < other.hour;

    return mins < other.mins;
}
/** Operator Override for == */
bool Time::operator==(const Time& other) const {
    return hour == other.hour && mins == other.mins;
}
