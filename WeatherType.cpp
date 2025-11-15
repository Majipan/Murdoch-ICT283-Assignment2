#include "WeatherType.h"

WeatherType::WeatherType()
    : date(), time(), speed(0), solrad(0), aatemp(0) {}

WeatherType::WeatherType(const Date& d, const Time& t, float spd, float rad, float air)
    : date(d), time(t), speed(spd), solrad(rad), aatemp(air) {}

// --- Getters ---
const Date& WeatherType::getDate() const { return date; }
const Time& WeatherType::getTime() const { return time; }
float WeatherType::getSpeed() const { return speed; }
float WeatherType::getSolarRad() const { return solrad; }
float WeatherType::getAirTemp() const { return aatemp; }

// --- Setters ---
void WeatherType::setDate(const Date& d) { date = d; }
void WeatherType::setTime(const Time& t) { time = t; }
void WeatherType::setSpeed(float s) { speed = s; }
void WeatherType::setSolarRad(float r) { solrad = r; }
void WeatherType::setAirTemp(float t) { aatemp = t; }
