
#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "WeatherData.h"
#include "WeatherMap.h"

class LoadData {
    public:
        /**
         * @brief Load wind records into the given container
         * @param weather_data Is the container for all weather data
         */
        void load(WeatherData& weather_data) const;
        /**
         * @brief Load wind records into the given container
         * Function Overload
         * @param weather_data Is the container for all weather data
         * @param weather_map Is the map for weather_data when using Bst
         */
        void load(WeatherData& weather_data, WeatherMap& weather_map) const;
};

#endif
