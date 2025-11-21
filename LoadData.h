
#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "WeatherData.h"
#include "WeatherMap.h"

class LoadData {
    public:
        /**
         * @brief Constructor function
         * Loads wind records into the given container
         * @param weather_map   The map for weather_data when using Bst
         * @param speedTree     BST of wind speed values
         * @param tempTree      BST of ambient temperature values
         * @param solarTree     BST of solar radiation values
         */
        void load(WeatherMap& weather_map, SpeedTree& speedTree, TempTree& tempTree, SolarTree& solarTree) const;

    private:
        /**
         * @brief Core implementation used by both overloads
         * @param weather_map    Optional pointer to WeatherMap for indexing. If nullptr, map is ignored.
         * @param speedTree     Optional speed BST pointer (can be nullptr)
         * @param tempTree      Optional temp BST pointer (can be nullptr)
         * @param solarTree     Optional solar BST pointer (can be nullptr)
         */
        void loadImpl(WeatherMap* weather_map, SpeedTree* speedTree, TempTree* tempTree, SolarTree* solarTree) const;
};

#endif
