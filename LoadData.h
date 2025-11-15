
#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "WeatherData.h"

class LoadData {
public:
    /**
     * @brief Load wind records into the given container
     */
    void load(WeatherData& weather_data) const;
};

#endif
