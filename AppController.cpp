#include "AppController.h"

/** Constructor with member initialisers */
AppController::AppController()
    : weather_data(), weather_map(), view(), model(), loader()
{
}

void AppController::run()
{
    std::cout << "[DEBUG] AppController::run() starting\n";
    /// Load data once at start
    std::cout << "[DEBUG] Calling loader.load(...)\n";
    loader.load(weather_data, weather_map);
    std::cout << "[DEBUG] loader.load(...) returned\n";
    std::cout << "[DEBUG] weather_data.size() = " << weather_data.size() << "\n";
    int input = 0;

    /// Menu Looping
    do {
        std::cout << "[DEBUG] Entering menu loop, about to call view.showMenu()\n";
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
