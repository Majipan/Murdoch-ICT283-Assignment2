#include "LoadData.h"
#include "WeatherMap.h"
#include "WeatherData.h"
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
void LoadData::load(WeatherMap& weather_map, SpeedTree& speedTree, TempTree& tempTree, SolarTree& solarTree) const
{
    loadImpl(&weather_map, &speedTree, &tempTree, &solarTree);
}

/// =================================================================================

void LoadData::loadImpl(WeatherMap* weather_map, SpeedTree* speedTree, TempTree* tempTree, SolarTree* solarTree) const
{
    std::cout << "[DEBUG] LoadData::loadImpl() starting\n";         /// remove later @@@@@@@@@@@
    /// ----------------------------------------
    /// Read data_source.txt to get the CSV path
    ifstream fileSource("data/data_source.txt");
    if (!fileSource.is_open()) {
        cerr << "Error opening data_source.txt" << endl;
        return;
    }

    int lineNumber = 1; /// remove later @@@@@@@@@@@
    string path;
    while (getline(fileSource, path)) {
        ++lineNumber; /// remove later @@@@@@@@@@@
        if (path.empty()) {
            continue;
        }
        std::cout << "[DEBUG] Opening data file: data/" << path << "\n";            /// remove later @@@@@@@@@@@
        /// ----------------------------------------
        /// Open each data file listed in data_source.txt
        ifstream file("data/" + path);
        if (!file.is_open()) {
            cerr << "Error opening source data file: " << path << endl;
            std::cout << "[DEBUG] File " << path << " is empty, skipping\n";        /// remove later @@@@@@@@@@@
            continue;   /// try next file
        }

        /// ----------------------------------------
        /// Read header and determine column indices
        string line;
        if (!getline(file, line)) {
            cout << "[WARN] File " << path << " is empty, skipping\n";      /// remove later @@@@@@@@@@@
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
            try{                                                    /// remove later @@@@@@@@@@@
            if (line.empty()) continue;

                /// --- Split the CSV row into columns ---
                stringstream ss(line);
                string token;
                int col = 0;

                string dateTime;
                string windSpd;
                string solarRad;
                string ambAir;

                while (getline(ss, token, ',')) {
                    if (col == dtIndex) {
                        dateTime = token;
                    } else if (col == spdIndex) {
                        windSpd = token;
                    } else if (col == radIndex) {
                        solarRad = token;
                    } else if (col == airIndex) {
                        ambAir = token;
                    }
                    ++col;
                }

                /// Skip rows with missing or N/A values
                if (dateTime.empty() ||
                    windSpd == "N/A" ||
                    solarRad == "N/A" ||
                    ambAir == "N/A") {
                    continue;
                }

                /// --- Parse date and time from dateTime ---
                /// Example format: "8/02/2010 9:00"
                string datePart, timePart;
                {
                    stringstream dt(dateTime);
                    getline(dt, datePart, ' ');
                    getline(dt, timePart);
                }

                int day = 0, month = 0, year = 0;
                {
                    stringstream ds(datePart);
                    string dTok, mTok, yTok;
                    getline(ds, dTok, '/');
                    getline(ds, mTok, '/');
                    getline(ds, yTok, '/');

                    day   = std::stoi(dTok);
                    month = std::stoi(mTok);
                    year  = std::stoi(yTok);
                }

                int hour = 0, minute = 0;
                {
                    stringstream ts(timePart);
                    string hTok, mTok;
                    getline(ts, hTok, ':');
                    getline(ts, mTok, ':');

                    hour   = std::stoi(hTok);
                    minute = std::stoi(mTok);
                }

                Date d(day, month, year);
                Time t(hour, minute);

                /// --- Parse numeric values ---
                float speed   = std::stof(windSpd);
                float solar   = std::stof(solarRad);
                float ambient = std::stof(ambAir);

                /// --- Insert into metric BSTs ---
                if (speedTree) {
                    SpeedRecord srec;
                    srec.date  = d;
                    srec.time  = t;
                    srec.speed = speed;
                    speedTree->insert(srec);   /// recursive insert sorted by speed
                }

                if (tempTree) {
                    TempRecord trec;
                    trec.date = d;
                    trec.time = t;
                    trec.temp = ambient;
                    tempTree->insert(trec);    /// sorted by temp
                }

                if (solarTree) {
                    SolarRecord rrec;
                    rrec.date  = d;
                    rrec.time  = t;
                    rrec.solar = solar;
                    solarTree->insert(rrec);   /// sorted by solar
                }

                /// --- Insert into WeatherMap (grouped by year/month) ---

                if (weather_map) {
                    /// Either use WeatherType + makeWeatherKey(record),
                    /// OR build key directly from d.getYear()/getMonth()
                    WeatherType rec;
                    rec.setDate(d);
                    rec.setTime(t);
                    rec.setSpeed(speed);
                    rec.setSolarRad(solar);
                    rec.setAirTemp(ambient);

                    WeatherKey key = makeWeatherKey(rec);
                    WeatherMonthlyStats& stats = (*weather_map)[key];
                    stats.speeds.insert(speed);
                    stats.temps.insert(ambient);
                    stats.solars.insert(solar);
                }
            }
        catch (const std::exception& ex) {                      /// remove later @@@@@@@@@@@
        std::cerr << "[WARN] Skipping bad row in " << path
                  << " at line " << lineNumber
                  << " due to parse error: " << ex.what()
                  << " | raw line: " << line << "\n";
        }}

        file.close();
        std::cout << "[DEBUG] Finished file: " << path << "\n";     /// remove later @@@@@@@@@@@
    }

    fileSource.close();
}
