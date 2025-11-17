#ifndef WEATHER_MAP_H
#define WEATHER_MAP_H

#include <map>
#include <string>
#include "WeatherType.h"

/** There is only Declarations in this file, all the logic is in the .cpp file */

/**
 * @brief Key type for weather records in the std::map
 * Textual key will be used, made from Date + Time. Format: "2010-01-01 13:20"
 */
using WeatherKey = std::string;

/**
 * @brief Map from Date+Time key to full WeatherType record
 * Option A: WeatherType is the map *value*, not the key
 */
using WeatherMap = std::map<WeatherKey, WeatherType>;

/**
 * @brief Helper to build a key from a WeatherType record
 * Format: YYYY-MM-DD HH:MM , this has to be trimmed for whitespace
 * @param rec A single WeatherType record
 */
WeatherKey makeWeatherKey(const WeatherType& rec);

#endif
