
#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "WeatherData.h"
#include "WeatherMap.h"

class LoadData {
    public:
        /**
         * @brief Constructor function
         * Loads wind records into the given container
         * @param weather_data  The container for all weather data
         * @param weather_map   The map for weather_data when using Bst
         */
        void load(WeatherData& weather_data, WeatherMap& weather_map) const;

    private:
        /**
         * @brief Core implementation used by both overloads.
         * @param weather_data   Destination container (BST / Vector).
         * @param weather_map    Optional pointer to WeatherMap for indexing. If nullptr, map is ignored.
         */
        void loadImpl(WeatherData& weather_data, WeatherMap* weather_map) const;
};

#endif
