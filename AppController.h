#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "WeatherMap.h"
#include "View.h"
#include "Model.h"
#include "LoadData.h"

/**
 * @brief Application controller coordinating View, Model, and data loading.
 */
class AppController {
public:
    /**
     * @brief Constructor
     * Members initialiser to start storing data in these containers
     */
    AppController();

    /** @brief Main application loop */
    void run();

private:
    /** @brief WeatherMap typedef */
    WeatherMap weather_map;
    /** @brief speedTree typedef */
    SpeedTree speedTree;
    /** @brief TempTree typedef */
    TempTree tempTree;
    /** @brief SolarTree typedef */
    SolarTree solarTree;

    /** @brief View Class (MVC) */
    View view;
    /** @brief Model Class (MVC) */
    Model model;
    /**
     * @brief LoadData class
     * Helps to load all the data from file
     */
    LoadData loader;
};

#endif
