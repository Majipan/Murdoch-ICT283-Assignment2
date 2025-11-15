#include "LoadData.h"
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

void LoadData::load(WindlogType& wind_data) const
{
    /// Open data_source.txt to get actual CSV path
    ifstream fileSource("data/data_source.txt");
    if (!fileSource.is_open()) {
        cerr << "Error opening data_source.txt" << endl;
        return;
    }

    string path;
    getline(fileSource, path);
    fileSource.close();

    /// Open the real data file
    ifstream file("data/" + path);
    if (!file.is_open()) {
        cerr << "Error opening source data file" << endl;
        return;
    }

    /// Read header line, find indexes
    string line;
    getline(file, line);
    stringstream ssHead(line);
    string header;
    int index = 0;

    int dtIndex = 0;
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

    /// Read data lines
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

        /// skip bad data (empty datetime)
        if (dateTime.empty()) {
            continue;
        }

        /// --- Date/Time parsing ---
        string dateVal, timeVal;
        stringstream dt(dateTime);
        getline(dt, dateVal, ' ');
        getline(dt, timeVal);

        string dayStr, monthStr, yearStr;
        stringstream dateSS(dateVal);
        getline(dateSS, dayStr, '/');
        getline(dateSS, monthStr, '/');
        getline(dateSS, yearStr);

        int day = std::stoi(dayStr);
        int month = std::stoi(monthStr);
        int year = std::stoi(yearStr);
        Date d(day, month, year);

        string hourVal, minVal;
        stringstream timeSS(timeVal);
        getline(timeSS, hourVal, ':');
        getline(timeSS, minVal);

        Time t;
        t.setHour(hourVal);
        t.setMins(minVal);

        /// Wind speed (m/s)
        float speed = std::stof(windSpd);

        /// Solar radiation
        float solar = std::stof(solarRad);

        /// Ambient air
        float ambient = std::stof(ambAir);

        /// Save record
        WindRecType record{ d, t, speed, solar, ambient };
        wind_data.append(record);
    }

    file.close();
}
