#include "AppController.h"

/** Constructor */
AppController::AppController()
    : weather_data(), view(), model(), loader()
{
}

void AppController::run()
{
    /// Load data once at start
    loader.load(weather_data);

    int input = 0;

    /// Menu Looping
    do {
        /// Tells the View to show the Menu to user and listen for an input
        input = view.showMenu();

        int month = 0;
        int year  = 0;

        /// Based on the input, tells the View to collect more input
        if (input == 1) {
            month = view.askMonth();
            year  = view.askYear();
        } else if (input != 5) {
            year = view.askYear();
        }

        /**  Based on the inputs, handle the menu options through Model and have view display the message */
        switch (input) {
        case 1:
            view.showMessage(model.handleOption1(weather_data, month, year));
            break;

        case 2:
            view.showMessage(model.handleOption2(weather_data, year));
            break;

        case 3:
            view.showMessage(model.handleOption3(weather_data, year));
            break;

        case 4:
            view.showMessage(model.handleOption4(weather_data, year));
            break;

        case 5:
            view.showMessage("Exiting the program");
            break;

        default:
            /// Shouldn't happen with current validation, otherwise something is seriously wrong
            break;
        }

    } while (input != 5);
}
