#ifndef VIEW_H
#define VIEW_H

#include <string>

class View {
public:
    /**
     * @brief To show the menu on the front end
     * @return The menu option selected
     */
    int showMenu() const;
    /**
     * @brief Ask user to input Month
     * @return The month in int
     */
    int askMonth() const;
    /**
     * @brief Ask user to input Year
     * @return The year in int
     */
    int askYear() const;

    /**
     * @brief General Function to show any messages to the console
     * @param message The message in string to display
     */
    void showMessage(const std::string& message) const;
};

#endif
