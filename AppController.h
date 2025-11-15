#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "WindData.h"
#include "View.h"
#include "Model.h"
#include "LoadData.h"

class AppController {
public:
    AppController();
    void run();    /// main application loop

private:
    WindlogType wind_data;
    View view;
    Model model;
    LoadData loader;
};

#endif
