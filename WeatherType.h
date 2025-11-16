#ifndef WEATHER_TYPE_H
#define WEATHER_TYPE_H

#include "Date.h"
#include "Time.h"

/**
 * @brief Represents a single row of weather log data.
 * Encapsulates: Date, Time, Wind Speed, Solar Radiation, Ambient Air Temperature.
 */
class WeatherType {
public:
    /** @brief Constructor */
    WeatherType();
    /**
     * @brief Constructor Overload
     * @param d Date Class
     * @param t Time Class
     * @param spd Speed value
     * @param rad Radiation Value
     * @param air Air Temperature
     */
    WeatherType(const Date& d, const Time& t, float spd, float rad, float air);

    /**
     * @brief Getter for Date
     * @return Date Class Pointer
     */
    const Date& getDate() const;
    /**
     * @brief Getter for Time
     * @return Time Class Pointer
     */
    const Time& getTime() const;
    /**
     * @brief Getter for Speed
     * @return Float value for Speed
     */
    float getSpeed() const;
    /**
     * @brief Getter for SolarRad
     * @return Float value for SolarRad
     */
    float getSolarRad() const;
    /**
     * @brief Getter for AirTemp
     * @return Float value for AirTemp
     */
    float getAirTemp() const;

    /**
     * @brief Setter for Date
     * @param d Date Class
     */
    void setDate(const Date& d);
    /**
     * @brief Setter for Time
     * @param t Time Class
     */
    void setTime(const Time& t);
    /**
     * @brief Setter for Speed
     * @param s Float value for speed
     */
    void setSpeed(float s);
    /**
     * @brief Setter for SolarRad
     * @param r Float value for SolarRad
     */
    void setSolarRad(float r);
    /**
     * @brief Setter for AirTemp
     * @param t Float value for AirTemp
     */
    void setAirTemp(float t);

private:
    /** @brief Date Class */
    Date date;
    /** @brief Time Class */
    Time time;
    /** @brief Speed Value */
    float speed;
    /** @brief Solar Radiation Value */
    float solrad;
    /** @brief Air Temperature Value */
    float aatemp;
};

/**
 * @brief Comparison operators < ordering WeatherType by Date+Time
 * @param lhs First WeatherType for comparison
 * @param rhs Second WeatherType for comparison
 * @return bool True/False result of the comparison
 */
bool operator<(const WeatherType& lhs, const WeatherType& rhs);
/**
 * @brief Comparison operators == ordering WeatherType by Date+Time
 * @param lhs First WeatherType for comparison
 * @param rhs Second WeatherType for comparison
 * @return bool True/False result of the comparison
 */
bool operator==(const WeatherType& lhs, const WeatherType& rhs);

#endif
