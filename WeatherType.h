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
    WeatherType();
    WeatherType(const Date& d, const Time& t, float spd, float rad, float air);

    // Getters
    const Date& getDate() const;
    const Time& getTime() const;
    float getSpeed() const;
    float getSolarRad() const;
    float getAirTemp() const;

    // Setters
    void setDate(const Date& d);
    void setTime(const Time& t);
    void setSpeed(float s);
    void setSolarRad(float r);
    void setAirTemp(float t);

private:
    Date date;
    Time time;
    float speed;
    float solrad;
    float aatemp;
};

#endif
