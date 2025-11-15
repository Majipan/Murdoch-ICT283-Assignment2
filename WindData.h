#ifndef WIND_DATA_H
#define WIND_DATA_H

#include "Date.h"
#include "Time.h"
#include "Vector.h"

/**
 * @brief Single wind record
 */
struct WindRecType {
    Date d;
    Time t;
    float speed;        // m/s
    float solrad;       // w/m2
    float aatemp;       // ambient air temperature
};

/**
 * @brief Container type for wind log
 */
typedef Vector<WindRecType> WindlogType;

#endif
