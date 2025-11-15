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
    AppController();
    void run();    /// main application loop

private:
    WeatherData weather_data;
    View view;
    Model model;
    LoadData loader;
};

#endif
