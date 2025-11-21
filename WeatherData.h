#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include "Bst.h"
#include "Date.h"
#include "Time.h"


/// =================================================================================


/**
 * @brief Node type for the speed BST.
 * Ordered by speed, then date, then time.
 */
struct SpeedRecord {
    Date  date;
    Time  time;
    float speed;

    bool operator<(const SpeedRecord& other) const;
};

/**
 * @brief Node type for the temperature BST.
 * Ordered by temp, then date, then time.
 */
struct TempRecord {
    Date  date;
    Time  time;
    float temp;

    bool operator<(const TempRecord& other) const;
};

/**
 * @brief Node type for the solar radiation BST.
 * Ordered by solar, then date, then time.
 */
struct SolarRecord {
    Date  date;
    Time  time;
    float solar;

    bool operator<(const SolarRecord& other) const;
};


/// =================================================================================


/**
 * @brief Individual BSTs for each metric
 * Each tree stores the raw float values for that metric.
 */
typedef Bst<SpeedRecord> SpeedTree;
typedef Bst<TempRecord> TempTree;
typedef Bst<SolarRecord> SolarTree;

#endif
