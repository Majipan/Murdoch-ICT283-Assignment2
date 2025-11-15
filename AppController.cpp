
#include "AppController.h"

AppController::AppController()
    : wind_data(), view(), model(), loader()
{
}

void AppController::run()
{
    /// Load data once at start
    loader.load(wind_data);

    /// Input value for the menu
    int input = 0;

    /**
     * @brief Loops the menu
    */
    do {
        input = view.showMenu();

        int month = 0;          /// Placeholder value for month
        int year = 0;           /// Placeholder value for year

        switch (input) {
        case 1:
            month = view.askMonth();
            year = view.askYear();
            view.showMessage(model.handleOption1(wind_data, month, year));
            break;

        case 2:
            year = view.askYear();
            view.showMessage(model.handleOption2(wind_data, year));
            break;

        case 3:
            year = view.askYear();
            view.showMessage(model.handleOption3(wind_data, year));
            break;

        case 4:
            year = view.askYear();
            view.showMessage(model.handleOption4(wind_data, year));
            break;

        case 5:
            view.showMessage("Exiting the program");
            break;

        default:
            /// Should not end up here otherwise there is something wrong with the menu input validation in View.cpp
            break;
        }

    } while (input != 5);
}
