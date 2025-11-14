#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

#include "Date.h"
#include "Time.h"
#include "Vector.h"

// --------------------------------------------------

typedef struct {
    Date d;
    Time t;
    float speed;        // m/s
    float solrad;       // w/m2
    float aatemp;
} WindRecType;

typedef Vector<WindRecType> WindlogType;

// ---Function prototype-----------------------------

void option1(WindlogType& wind_data, int month, int year);
void option2(WindlogType& wind_data, int year);
void option3(WindlogType& wind_data, int year);
void option4(WindlogType& wind_data, int year);
void loadData(WindlogType& wind_data);
int interfaceController(WindlogType& wind_data);
int menu();
int askMonth();
int askYear();
string convMonth(int month);
double convRads(int value);
float calculateMean(WindlogType& wind_data, int month, int year, int dataType);
double calculateStandardDeviation(WindlogType& wind_data, float avg, int month, int year, int dataType);

// --------------------------------------------------

using namespace std;

// --------------------------------------------------

int main()
{
    /// allow console to show in UTF=8 for the square(superscript) symbol
    SetConsoleOutputCP(CP_UTF8);

    /// create vector, then load the data
    WindlogType wind_data;
    loadData(wind_data);

    /// start interface
    int interfaceCtrl = interfaceController(wind_data);


    return 0;
}


/** ----------------------------------------------------------------------------
 * @brief Interface controller
 * Controller that does all the calling to the functions and menu
 */
int interfaceController(WindlogType& wind_data)
{
    int input = 0;

    /** ----------------------------------------
     * @brief Input, Processing and Output
     * This loop takes the user input, processes the data and generates an output.
     * It will continue until the user selects option 5
     * @param dataType = 1 --> Wind Speed
     * @param dataType = 2 --> Solar Radiation
     * @param dataType = 3 --> Ambient Air Temperature
     * @return integer as a formality, mainly to direct the flow back to main()
     */
     do {

        /** -------------------
         * @brief INPUT      */
        input = menu();         /// menu input
        int month;              /// month input
        int year;              /// month input

        if (input == 1) {
            month = askMonth();
            year = askYear();
        } else if (input != 5) {
            year = askYear();   /// year input
        }

        /** ------------------------------
         * @brief PROCESSING and OUTPUT */

        switch (input) {
            case 1:
                option1(wind_data, month, year);
                break;

            case 2:
                option2(wind_data, year);
                break;

            case 3:
                option3(wind_data, year);
                break;

            case 4:
                option4(wind_data, year);
                break;

            case 5:
                cout << "Exiting the program" << endl;
                break;
        }

        cout << endl;

    } while (input != 5);

    return 0;       /// return to main and exit the program

}


/** ----------------------------------------------------------------------------
 * @brief Option 1
 * @return void
 */
void option1(WindlogType& wind_data, int month, int year) {
    /// processing
    float avg =  round(calculateMean(wind_data, month, year, 1) * 36) / 10;        /// convert to km/h and 1 decimal
    float stdDev = calculateStandardDeviation(wind_data, avg, month, year, 1);

    /// output
    if (avg != 0) {
        cout << endl << convMonth(month) << " " << year << ":" << endl;
        cout << "Average speed: " << avg << " km/h" << endl;
        cout << " Sample stdev: " << stdDev << endl;
    } else {
        cout << convMonth(month) << " " << year << ": No Data" << endl;
    }
}


/** ----------------------------------------------------------------------------
 * @brief Option 2
 * @return void
 */
void option2(WindlogType& wind_data, int year) {

    cout << endl << year << endl;

    /// print month by month
    for (int i=1; i < 13; ++i) {
        float avg = round(calculateMean(wind_data, i, year, 3) * 36) / 10;

        if (avg == 0) {
            cout << convMonth(i) << ": No Data" << endl;
        } else {
            cout << convMonth(i) << ": average: " << avg
            << " degrees C, stdev: " << calculateStandardDeviation(wind_data, avg, i, year, 1) << endl;;
        }
    }

}


/** ----------------------------------------------------------------------------
 * @brief Option 3
 * @return void
 */
void option3(WindlogType& wind_data, int year) {

    cout << endl << year << endl;

    /// print month by month
    for (int i=1; i < 13; ++i) {
        float avg = calculateMean(wind_data, i, year, 2);
        avg = convRads(avg);        /// convert to kWh/m2

        if (avg == 0) {
            cout << convMonth(i) << ": No Data" << endl;
        } else {
            cout << convMonth(i) << ": " << avg
            << " kWh/m" << "\u00B2" << endl;;
        }
    }

}


/** ----------------------------------------------------------------------------
 * @brief Option 4
 * @return void
 */
void option4(WindlogType& wind_data, int year) {
    ofstream ofile( "WindTempSolar.csv" );
    ofile << year << '\n';

    /// print month by month
    for (int i=1; i < 13; ++i) {
        float avgWind = calculateMean(wind_data, i, year, 1);
        float stdDevWind = calculateStandardDeviation(wind_data, avgWind, i, year, 1);
        float avgRads = calculateMean(wind_data, i, year, 2);
        avgRads = convRads(avgRads);        /// convert to kWh/m2
        float stdDevRads = calculateStandardDeviation(wind_data, avgRads, i, year, 1);
        float avgTemp = calculateMean(wind_data, i, year, 3);



        ofile << convMonth(i) << "," << avgWind << "(" << stdDevWind << "),"
              << avgRads << "(" << stdDevRads << ")," << avgTemp << '\n';
    }

    cout << "WindTempSolar.csv successfully generated." << endl;

}


/** ----------------------------------------------------------------------------
 * @brief Load the data and sort it into the Vector struct
 * @return void
 */
void loadData(WindlogType& wind_data)
{
    /** ----------------------------------------
     * @brief Opening the file with the source data path
     */
    ifstream fileSource("data/data_source.txt");
    if (!fileSource.is_open()) {
        cerr << "Error opening data_source.txt" << endl;
    }


    /** @brief Obtain source file name */
    string path;                    /// var to store the name of the data source
    getline(fileSource, path);      /// get the source file name
    fileSource.close();             /// close the file stream


    /** ----------------------------------------
     * @brief Load the data source
     */
    ifstream file("data/"+path);
    if (!file.is_open()) {
        cerr << "Error opening source data file" << endl;
    }


    /** ----------------------------------------
     * @brief Loop the header to store the index of the columns
     */
    string line;                    /// store lines
    getline(file, line);            /// get header
    stringstream ssHead(line);      /// read lines
    string header;                  /// store individual header values
    int index = 0;                  /// index of the columns
    /// Index of the columns to save
    int dtIndex = 0;                /// Date Time column index
    int spdIndex = 0;               /// Wind-speed column index
    int radIndex = 0;               /// Solar Radiation column index
    int airIndex = 0;               /// Ambient Air column index

    /** @brief Obtain column index */
    while(getline(ssHead, header, ',')) {
        /// check for the right column header
        if (header == "WAST") {
            dtIndex = index;
        } else if (header == "S") {
            spdIndex = index;
        } else if (header == "SR") {
            radIndex = index;
        } else if (header == "T") {
            airIndex = index;
        }

        ++index;
    }


    /** ----------------------------------------
     * @brief Loop data rows and save the data into the struct
     */
    while ( getline(file, line) ){
        stringstream ss(line);      /// stringstream for each line
        string value;               /// stores the value of each column
        index = 0;                  /// reset index

        /// Data values
        string dateTime;
        string windSpd;
        string solarRad;
        string ambAir;

        /// comma delimiter, save each values based on the index
        while ( getline(ss, value, ',') ) {
            if (index == dtIndex)           /// Date Time
                dateTime = value;
            else if (index == spdIndex)     /// Wind Speed
                windSpd = value;
            else if (index == radIndex)     /// Solar Radiation
                solarRad = value;
            else if (index == airIndex)     /// Ambient Air
                ambAir = value;

            ++index;
        }


        /** @brief skip lines that have bad data
         *  Only skip when date field is empty
         */
        // stop being sneaky  >:(
        if (dateTime.empty()) {
            continue;
        }


        /** @brief Save Date Time Value */
        // --- Split Date/Time ---
        string dateVal, timeVal;
        stringstream dt(dateTime);
        getline(dt, dateVal, ' ');
        getline(dt, timeVal);

        // --- Sort the Date ---
        string dayStr, monthStr, yearStr;
        stringstream dateSS(dateVal);
        getline(dateSS, dayStr, '/');
        getline(dateSS, monthStr, '/');
        getline(dateSS, yearStr);

        // --- Save into Date Class ---
        int day = stoi(dayStr);
        int month = stoi(monthStr);
        int year = stoi(yearStr);
        Date d(day, month, year);

        // --- Sort the Time ---
        string hourVal, minVal;
        stringstream timeSS(timeVal);
        getline(timeSS, hourVal, ':');
        getline(timeSS, minVal);

        // --- Save time the time Class ---
        Time t;
        t.setHour(hourVal);
        t.setMins(minVal);


        /** @brief Save Wind Speed Value */
        // --- Save wind speed ---
        float speed = stof(windSpd);    // save the windspeed in m/s


        /** @brief Save Solar Radiation Value */
        // --- Save wind speed ---
        float solar = stof(solarRad);   // save the windspeed in m/s


        /** @brief Save Ambient Air Temperature Value */
        // --- Save wind speed ---
        float ambient = stof(ambAir);   // save the windspeed in m/s


        /** @brief Save Record into the struct */
        // --- Save the record into the struct
        WindRecType record{d, t, speed, solar, ambient};
        wind_data.append(record);

    }

    /** @brief Close the file stream */
    file.close();                  /// close the file stream
}


/** ----------------------------------------------------------------------------
 * @brief Loop the menu until a valid input is obtained
 * @return the menu option selected in integer
 */
int menu()
{
    int option;
	do
	{
		cout << "1 - The average wind speed and sample standard deviation for this wind speed given a specified month and year" << endl;
		cout << "2 - Average ambient air temperature and sample standard deviation for each month of a specified year" << endl;
		cout << "3 - Total solar radiation in kWh/m" << "\u00B2" << " for each month of the year" << endl;
		cout << "4 - Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m" << "\u00B2" << " for each month of a specified year" << endl;
		cout << "5 - Exit the program" << endl;
		cin >> option;

		if ( !option || (option <1 && option >5) ) {
            cout << "Invalid input" << endl;        /// error handling for invalid input
            option = 0;                             /// reset the option variable
		}

	} while (option == 0);                          ///loop again if condition fails

	return option;
}


/** ----------------------------------------------------------------------------
 * @brief Ask user for month input
 * @return month in integer
 */
int askMonth() {
    int month;

    do
	{
		cout << "Enter Month(1-12): ";
		cin >> month;

		if ( !month || (month <1 && month >12) ) {
            cout << "Invalid input" << endl;        /// error handling for invalid input
            month = 0;                              /// reset the option variable
		}

	} while (month == 0);                           ///loop again if condition fails

	return month;
}


/** ----------------------------------------------------------------------------
 * @brief Ask user for year input
 * @return year in integer
 */
int askYear() {
    int year;

    do
	{
		cout << "Enter Year: ";
		cin >> year;

		if ( !year ) {
            cout << "Invalid input" << endl;        /// error handling for invalid input
            year = 0;                               /// reset the year variable
		}

	} while (year == 0);                            ///loop again if condition fails

	return year;
}


/** ----------------------------------------------------------------------------
 * @brief Convert month from Int to String
 * @return month in string
 */
string convMonth(int month) {
    static const string monthNames[13] {
        "SKIP", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    return monthNames[month];
}


/** ----------------------------------------------------------------------------
 * @brief Convert month from Int to String
 * @return kWh/m2
 */
double convRads(int value) {
    /// from watts/m2 10mins interval to kWh/m2
    double wattsPerHour = value / 6;
    double kiloWattsPerHour = wattsPerHour / 1000;

    return kiloWattsPerHour;
}


/** ----------------------------------------------------------------------------
 * @brief Get the average
 * All the menu option uses this function to calculate mean as part of high cohesion & modular design
 * @param dataType = 1 --> Wind Speed
 * @param dataType = 2 --> Solar Radiation
 * @param dataType = 3 --> Ambient Air Temperature
 * @return average with 1 decimal point
 */
float calculateMean(WindlogType& wind_data, int month, int year, int dataType) {
    float sum = 0;
    int counter = 0;        /// for counting how many rows

    for (int i = 0; i < wind_data.size(); ++i) {
        /// check if the month and year matches
        if (wind_data[i].d.getMonth() == month && wind_data[i].d.getYear() == year) {
            if (dataType==1) {
                sum += wind_data[i].speed;
                ++counter;

            } else if (dataType==2) {
                /// if higher than 100, add into sum, else increase skip to make the division correct later
                if (wind_data[i].solrad >= 100){
                    sum += wind_data[i].solrad;
                    ++counter;
                }

            } else if (dataType==3) {
                sum += wind_data[i].aatemp;
                ++counter;
            }

        /// early escape clause so that the application doesn't read through the entire data
        /// needs to be same or higher in years, and higher in months
        } else if (wind_data[i].d.getYear() >= year && wind_data[i].d.getMonth() > month) {
            break;
        }

    }

    if (sum != 0) {
        sum = sum / counter;
        sum = round( sum * 10 ) / 10;
    }

    return sum;
}


/** ----------------------------------------------------------------------------
 * @brief Get the Standard Deviation
 * All the menu option uses this function to calculate standard deviation as part of high cohesion & modular design
 * @param dataType = 1 --> Wind Speed
 * @param dataType = 2 --> Solar Radiation
 * @param dataType = 3 --> Ambient Air Temperature
 * @return standard deviation in 1 decimal point
 */
double calculateStandardDeviation(WindlogType& wind_data, float avg, int month, int year, int dataType) {
    double sumSquaredDiff = 0;

    for (int i = 0; i < wind_data.size(); ++i) {
        /// check if the month and year matches
        if (wind_data[i].d.getMonth() == month && wind_data[i].d.getYear() == year) {
            /// val is the value based on the dataType
            float val;
            if (dataType==1) val = wind_data[i].speed;
            else if (dataType==2) val = wind_data[i].solrad;
            else if (dataType==3) val = wind_data[i].aatemp;

            double diff = val - avg;
            sumSquaredDiff += diff * diff;                  /// manual squaring
        }
    }

    double variance = sumSquaredDiff / (wind_data.size() -1);
    double squareRoot = sqrt(variance);
    float stdDev = round( squareRoot * 10 ) / 10;           /// round to 1 decimal

    return stdDev;
}
