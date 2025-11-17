#include "LoadData.h"
#include "WeatherMap.h"
#include <fstream>
#include <sstream>
#include <iostream>

using std::ifstream;
using std::stringstream;
using std::string;
using std::getline;
using std::cerr;
using std::endl;
using std::stof;

void LoadData::load(WeatherData& weather_data) const
{
    /// ----------------------------------------
    /// Read data_source.txt to get the CSV path
    ifstream fileSource("data/data_source.txt");
    if (!fileSource.is_open()) {
        cerr << "Error opening data_source.txt" << endl;
        return;
    }

    string path;
    getline(fileSource, path);
    fileSource.close();

    /// ----------------------------------------
    /// Open the actual data file
    ifstream file("data/" + path);
    if (!file.is_open()) {
        cerr << "Error opening source data file" << endl;
        return;
    }

    /// ----------------------------------------
    /// Read header and determine column indices
    string line;
    getline(file, line);
    stringstream ssHead(line);
    string header;
    int index = 0;

    int dtIndex  = 0;
    int spdIndex = 0;
    int radIndex = 0;
    int airIndex = 0;

    while (getline(ssHead, header, ',')) {
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

    /// ----------------------------------------
    /// Read data rows
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        index = 0;

        string dateTime;
        string windSpd;
        string solarRad;
        string ambAir;

        while (getline(ss, value, ',')) {
            if (index == dtIndex)
                dateTime = value;
            else if (index == spdIndex)
                windSpd = value;
            else if (index == radIndex)
                solarRad = value;
            else if (index == airIndex)
                ambAir = value;

            ++index;
        }

        /// Skip lines with empty date/time
        if (dateTime.empty()) {
            continue;
        }

        /// --- Split Date/Time ---
        string dateVal, timeVal;
        stringstream dt(dateTime);
        getline(dt, dateVal, ' ');
        getline(dt, timeVal);

        /// --- Parse date ---
        string dayStr, monthStr, yearStr;
        stringstream dateSS(dateVal);
        getline(dateSS, dayStr, '/');
        getline(dateSS, monthStr, '/');
        getline(dateSS, yearStr);

        int day   = std::stoi(dayStr);
        int month = std::stoi(monthStr);
        int year  = std::stoi(yearStr);
        Date d(day, month, year);

        /// --- Parse time ---
        string hourVal, minVal;
        stringstream timeSS(timeVal);
        getline(timeSS, hourVal, ':');
        getline(timeSS, minVal);

        int hour = std::stoi(hourVal);
        int minute = std::stoi(minVal);
        Time t(hour, minute);

        /// --- Parse numeric values ---
        float speed   = std::stof(windSpd);
        float solar   = std::stof(solarRad);
        float ambient = std::stof(ambAir);

        /// --- Create WeatherType record ---
        WeatherType record;
        record.setDate(d);
        record.setTime(t);
        record.setSpeed(speed);
        record.setSolarRad(solar);
        record.setAirTemp(ambient);

        /// Insert to container
        weather_data.insert(record);
    }

    file.close();
}
