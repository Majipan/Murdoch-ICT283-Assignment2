#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "Vector.h"
#include "WeatherData.h"
#include "WeatherMap.h"


/**
 * @brief Business logic for processing weather data.
 */
class Model {
public:
    /**
     * @brief Constructor
     * @param data      BST container
     * @param map       std::map data
     * @param speedTree BST for wind speed data
     * @param tempTree  BST for temperature data
     * @param solarTree BST for Solar radiation data
     */
    Model(WeatherMap&   map,
          SpeedTree&    speedTree,
          TempTree&     tempTree,
          SolarTree&    solarTree);

    /**
     * @brief Option 1:
     * Average wind speed (km/h) and sample standard deviation for a specified month and year.
     * @return the string to show on screen
     */
    std::string handleOption1(const WeatherMap& weather_map, int month, int year) const;

    /**
     * @brief Option 2:
     * Average ambient air temperature and sample standard deviation for each month of a specified year.
     * @return the string to show on screen
     */
    std::string handleOption2(const WeatherMap& weather_map, int year) const;

    /**
     * @brief Option 3:
     * Sample Pearson Correlation Coefficient (sPCC) for a user specified month across all years for the combinations:
     *   S_T (speed, temperature),
     *   S_R (speed, solar),
     *   T_R (temperature, solar).
     * @return the string to show on screen
     */
    std::string handleOption3(const WeatherMap& weather_map, int month) const;

    /**
     * @brief Option 4:
     * Average wind speed (km/h), average ambient air temperature and
     * total solar radiation (kWh/m2) for each month of a specified year.
     * Standard deviation and MAD are printed as (stdev, mad) next to averages.
     * Also writes a CSV file "WindTempSolar.csv".
     * @return the string to show on screen
     */
    std::string handleOption4(const WeatherMap& weather_map, int year) const;


private:
    /** @brief Variables */
    WeatherMap& weather_map;
    SpeedTree&  speedTree;
    TempTree&   tempTree;
    SolarTree&  solarTree;

    /**
     * @brief Convert int month into string alias
     * @param month     Represents Month in int
     * @return Month in string alias
     */
    std::string convMonth(int month) const;
    /**
     * @brief Converts watts per hour to kilowatts per hour
     * @param value     Represents watts per hour
     * @return Kilo watts per hour
     */
    double convRads(double value) const;

    /**
     * @brief Calculate the mean data for the selected month and year
     * @param values
     * @return the double in float
     */
    double mean(const Vector<float>& values) const;

    /**
     * @brief Calculates the standard deviation
     * @param values
     * @param mean      Represents mean in double
     * @return standard sample deviation in double
     */
    double sampleStdDev(const Vector<float>& values, double mean) const;

    /**
     * @brief Calculates the standard deviation
     * @param values
     * @param mean      Represents mean in double
     * @return mean absolute deviation in double
     */
    double meanAbsoluteDeviation(const Vector<float>& values, double mean) const;

    /**
     * @brief Calculates the standard deviation
     * @param xs
     * @param ys
     * @return mean sPCC in double
     */
    double pearsonCorrelation(const Vector<float>& xs, const Vector<float>& ys) const;
};

#endif
