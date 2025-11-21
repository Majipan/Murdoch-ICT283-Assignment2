#include "WeatherData.h"

bool SpeedRecord::operator<(const SpeedRecord& other) const {
    if (speed < other.speed) return true;
    if (other.speed < speed) return false;

    if (date < other.date)   return true;
    if (other.date < date)   return false;

    return time < other.time;
}

bool TempRecord::operator<(const TempRecord& other) const {
    if (temp < other.temp) return true;
    if (other.temp < temp) return false;

    if (date < other.date)  return true;
    if (other.date < date)  return false;

    return time < other.time;
}

bool SolarRecord::operator<(const SolarRecord& other) const {
    if (solar < other.solar) return true;
    if (other.solar < solar) return false;

    if (date < other.date)   return true;
    if (other.date < date)   return false;

    return time < other.time;
}
