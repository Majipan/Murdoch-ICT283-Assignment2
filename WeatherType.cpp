#include "WeatherType.h"

/** Constructor */
WeatherType::WeatherType() : date(), time(), speed(0), solrad(0), aatemp(0) {}

/** Constructor Overload */
WeatherType::WeatherType(const Date& d, const Time& t, float spd, float rad, float air)
                        : date(d), time(t), speed(spd), solrad(rad), aatemp(air) {}

/// =================================================================================

/** Getters */
const Date& WeatherType::getDate() const { return date; }
const Time& WeatherType::getTime() const { return time; }
float WeatherType::getSpeed() const { return speed; }
float WeatherType::getSolarRad() const { return solrad; }
float WeatherType::getAirTemp() const { return aatemp; }

/** Setters */
void WeatherType::setDate(const Date& d) { date = d; }
void WeatherType::setTime(const Time& t) { time = t; }
void WeatherType::setSpeed(float s) { speed = s; }
void WeatherType::setSolarRad(float r) { solrad = r; }
void WeatherType::setAirTemp(float t) { aatemp = t; }

/// =================================================================================

/** Operator Overload < */
bool operator<(const WeatherType& lhs, const WeatherType& rhs) {
    /// Compare dates both ways
    if (lhs.getDate() < rhs.getDate()) return true;
    if (rhs.getDate() < lhs.getDate()) return false;

    /// Dates are equal; compare times both ways as well
    if (lhs.getTime() < rhs.getTime()) return true;
    if (rhs.getTime() < lhs.getTime()) return false;

    /// Same Date+Time => not less
    return false;
}

/** Operator Overload == */
bool operator==(const WeatherType& lhs, const WeatherType& rhs) {
    return lhs.getDate() == rhs.getDate() &&
           lhs.getTime() == rhs.getTime();
    // Note to self: speed, solar, air temp are NOT part of equality for key purposes
}
