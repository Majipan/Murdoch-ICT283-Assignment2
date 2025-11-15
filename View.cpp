#include "View.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;


/** ----------------------------------------------------------------------------------
 * @brief Menu display and input
 * @return Returns an integer that represents the menu option selected
 */
int View::showMenu() const
{
    int option;
    do
    {
        cout << endl;       /// Formatting for better legibility for the user
        cout << "1 - The average wind speed and sample standard deviation for this wind speed given a specified month and year" << endl;
        cout << "2 - Average ambient air temperature and sample standard deviation for each month of a specified year" << endl;
        cout << "3 - Total solar radiation in kWh/m" << "\u00B2" << " for each month of the year" << endl;
        cout << "4 - Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m" << "\u00B2" << " for each month of a specified year" << endl;
        cout << "5 - Exit the program" << endl;
        cin >> option;

        /// Menu validation to prevent invalid inputs
        if (!option || option < 1 || option > 5) {
            cout << "Invalid input" << endl;
            option = 0;
        }

    } while (option == 0);

    return option;
}


/** ----------------------------------------------------------------------------------
 * @brief Ask the user for an input for Month
 * @return Returns an integer to represent the Month
 */
int View::askMonth() const
{
    int month;

    do
    {
        cout << "Enter Month(1-12): ";
        cin >> month;

        if (!month || (month < 1 && month > 12)) {
            cout << "Invalid input" << endl;
            month = 0;
        }

    } while (month == 0);

    return month;
}


/** ----------------------------------------------------------------------------------
 * @brief Ask the user for an input for Year
 * @return Returns an integer to represent the Year
 */
int View::askYear() const
{
    int year;

    do
    {
        cout << "Enter Year(YYYY): ";
        cin >> year;

        if (!year) {
            cout << "Invalid input" << endl;
            year = 0;
        }

    } while (year == 0);

    return year;
}

void View::showMessage(const std::string& message) const
{
    cout << message << endl;
}
