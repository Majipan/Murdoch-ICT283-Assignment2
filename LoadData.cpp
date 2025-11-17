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
using std::cout;

/// =================================================================================

/** Constructor */
void LoadData::load(WeatherData& weather_data) const{
    loadImpl(weather_data, nullptr);
}

/** Constructor Overload with std::map */
void LoadData::load(WeatherData& weather_data, WeatherMap& weather_map) const{
    loadImpl(weather_data, &weather_map);
}

/// =================================================================================

void LoadData::loadImpl(WeatherData& weather_data, WeatherMap* weather_map) const
{
    std::cout << "[DEBUG] LoadData::loadImpl() starting\n";
    /// ----------------------------------------
    /// Read data_source.txt to get the CSV path
    ifstream fileSource("data/data_source.txt");
    if (!fileSource.is_open()) {
        cerr << "Error opening data_source.txt" << endl;
        return;
    }


    string path;
    while (getline(fileSource, path)) {
        if (path.empty()) {
            continue;
        }
        std::cout << "[DEBUG] Opening data file: data/" << path << "\n";
        /// ----------------------------------------
        /// Open each data file listed in data_source.txt
        ifstream file("data/" + path);
        if (!file.is_open()) {
            cerr << "Error opening source data file: " << path << endl;
            std::cout << "[DEBUG] File " << path << " is empty, skipping\n";
            continue;   // try next file
        }

        /// ----------------------------------------
        /// Read header and determine column indices
        string line;
        if (!getline(file, line)) {
            cout << "[WARN] File " << path << " is empty, skipping\n";
            file.close();
            continue;   /// empty file
        }

        stringstream ssHead(line);
        string header;
        int index = 0;

        int dtIndex  = -1;
        int spdIndex = -1;
        int radIndex = -1;
        int airIndex = -1;

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

        /// Basic safety check
        if (dtIndex < 0 || spdIndex < 0 || radIndex < 0 || airIndex < 0) {
            cerr << "Required columns not found in file: " << path << endl;
            file.close();
            continue;
        }

        /// ----------------------------------------
        /// Read data rows
        while (getline(file, line)) {
            try{
            stringstream ss(line);
            string value;
            index = 0;

            string dateTime;
            string windSpd;
            string solarRad;
            string ambAir;

            while (getline(ss, value, ',')) {
                if (index == dtIndex) {
                    dateTime = value;
                } else if (index == spdIndex) {
                    windSpd = value;
                } else if (index == radIndex) {
                    solarRad = value;
                } else if (index == airIndex) {
                    ambAir = value;
                }
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
            string hourStr, minStr;
            stringstream timeSS(timeVal);
            getline(timeSS, hourStr, ':');
            getline(timeSS, minStr);

            int hour   = std::stoi(hourStr);
            int minute = std::stoi(minStr);

            Time t(hour, minute);   /// uses new int-based Time

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

            /// Insert into main container (BST or Vector, via WeatherData typedef)
            weather_data.insert(record);

            /// Optionally build std::map index depending if its sent as a parameter
            if (weather_map) {
                WeatherKey key = makeWeatherKey(record);
                (*weather_map)[key] = record;
            }

        }
        catch (const std::exception& ex) {
            std::cerr << "[WARN] Skipping bad row in " << path
                      << " due to parse error: " << ex.what() << "\n";
            // continue to next line
        }}

        file.close();
        std::cout << "[DEBUG] Finished file: " << path << "\n";
    }

    fileSource.close();
}
