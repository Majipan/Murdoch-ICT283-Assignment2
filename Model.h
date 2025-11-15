#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "WeatherData.h"

/**
 * @brief Business logic for processing weather data.
 */
class Model {
public:
    // Option handlers: compute results and return text for the View
    std::string handleOption1(const WeatherData& weather_data, int month, int year) const;
    std::string handleOption2(const WeatherData& weather_data, int year) const;
    std::string handleOption3(const WeatherData& weather_data, int year) const;
    std::string handleOption4(const WeatherData& weather_data, int year) const;

private:
    std::string convMonth(int month) const;
    double convRads(int value) const;

    float calculateMean(const WeatherData& weather_data, int month, int year, int dataType) const;

    double calculateStandardDeviation(const WeatherData& weather_data, float avg, int month, int year, int dataType) const;
};

#endif
