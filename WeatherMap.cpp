#include "WeatherMap.h"

WeatherKey makeWeatherKey(const WeatherType& rec) {
    WeatherKey key;
    key.year  = rec.getDate().getYear();
    key.month = rec.getDate().getMonth();
    return key;
}

bool WeatherKey::operator<(const WeatherKey& other) const {
    /// Checks if year is the same
    if (year != other.year) {
        return year < other.year;   /// true/false
    }
    return month < other.month;     /// true/false
}
