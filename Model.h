#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "WindData.h"

class Model {
public:
    // Option handlers: same logic, but return strings instead of printing
    std::string handleOption1(const WindlogType& wind_data, int month, int year) const;
    std::string handleOption2(const WindlogType& wind_data, int year) const;
    std::string handleOption3(const WindlogType& wind_data, int year) const;
    std::string handleOption4(const WindlogType& wind_data, int year) const;

private:
    std::string convMonth(int month) const;
    double convRads(int value) const;

    float calculateMean(const WindlogType& wind_data, int month, int year, int dataType) const;

    double calculateStandardDeviation(const WindlogType& wind_data, float avg, int month, int year, int dataType) const;
};

#endif
