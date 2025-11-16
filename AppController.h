#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "WeatherData.h"
#include "View.h"
#include "Model.h"
#include "LoadData.h"

/**
 * @brief Application controller coordinating View, Model, and data loading.
 */
class AppController {
public:
    /** @brief Constructor */
    AppController();

    /** @brief Main application loop */
    void run();

private:
    /** @brief WeatherData typedef */
    WeatherData weather_data;
    /** @brief View Class (MVC) */
    View view;
    /** @brief Model Class (MVC) */
    Model model;
    /**
     * @brief LoadData class
     * Helps to load all the data
     */
    LoadData loader;
};

#endif
