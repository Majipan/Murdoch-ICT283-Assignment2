#ifndef WEATHER_MAP_H
#define WEATHER_MAP_H

#include <map>
#include <string>
#include "Vector.h"
#include "WeatherType.h"

/** There is only Declarations in this file, all the logic is in the .cpp file */

/**
 * @brief A struct to contain Date & Time
 * An operator override to compare Date & Time
 */
struct WeatherKey {
    int year;
    int month;

    /// Compare by year then month
    bool operator<(const WeatherKey& other) const;
};

/**
 * @brief Holds all the raw data for one row
 */
struct WeatherMonthlyStats {
    Vector<float> speeds;
    Vector<float> temps;
    Vector<float> solars;
};

/**
 * @brief Map from Date+Time key to full WeatherType record
 * Option A: WeatherType is the map *value*, not the key
 */
using WeatherMap = std::map<WeatherKey, WeatherMonthlyStats>;

/**
 * @brief Helper to build a key from a WeatherType record
 * Format: YYYY-MM-DD HH:MM , this has to be trimmed for whitespace
 * This helps to easily generate the key when attempting to insert
 * @param rec A single WeatherType record
 */
WeatherKey makeWeatherKey(const WeatherType& rec);


#endif
