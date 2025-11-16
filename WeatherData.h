#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include "Bst.h"
#include "WeatherType.h"

/**
 * @brief Container type for weather logs to be used across multiple classes
 * For this assignment, i hot-swapped Vector<WeatherType> to Bst<WeatherType> without making any further changes to WeatherData.h
 */
typedef Bst<WeatherType> WeatherData;

#endif
