#include "Time.h"
#include <iostream>
#include <string>

using namespace std;

/** @brief Main Constructor */
Time::Time() : hour(""), mins("") {}

/** @brief Constructor Overload */
Time::Time(string h, string m) : hour(h), mins(m) {}

const string Time::getTime() const {
    return hour+":"+mins;
}

void Time::setHour(string h) { hour = h; }
void Time::setMins(string m) { mins = m; }
