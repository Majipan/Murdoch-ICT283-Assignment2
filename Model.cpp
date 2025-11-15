#include "Model.h"
#include <sstream>
#include <cmath>
#include <fstream>

using std::string;
using std::ostringstream;
using std::ofstream;
using std::endl;

std::string Model::handleOption1(const WeatherData& weather_data, int month, int year) const
{
    ostringstream out;

    // convert to km/h and round to 1 decimal
    float avg = std::round(calculateMean(weather_data, month, year, 1) * 36) / 10;
    float stdDev = static_cast<float>(
        calculateStandardDeviation(weather_data, avg, month, year, 1)
    );

    if (avg != 0) {
        out << std::endl << convMonth(month) << " " << year << ":" << std::endl;
        out << "Average speed: " << avg << " km/h" << std::endl;
        out << " Sample stdev: " << stdDev;
    } else {
        out << convMonth(month) << " " << year << ": No Data";
    }

    return out.str();
}

std::string Model::handleOption2(const WeatherData& weather_data, int year) const
{
    ostringstream out;

    out << std::endl << year << std::endl;

    for (int i = 1; i < 13; ++i) {
        float avg = std::round(calculateMean(weather_data, i, year, 3) * 36) / 10;

        if (avg == 0) {
            out << convMonth(i) << ": No Data" << std::endl;
        } else {
            out << convMonth(i) << ": average: " << avg
                << " degrees C, stdev: "
                << calculateStandardDeviation(weather_data, avg, i, year, 1)
                << std::endl;
        }
    }

    return out.str();
}

std::string Model::handleOption3(const WeatherData& weather_data, int year) const
{
    ostringstream out;

    out << std::endl << year << std::endl;

    for (int i = 1; i < 13; ++i) {
        float avg = calculateMean(weather_data, i, year, 2);
        // original convRads took int; cast to preserve original semantics
        avg = static_cast<float>(convRads(static_cast<int>(avg)));

        if (avg == 0) {
            out << convMonth(i) << ": No Data" << std::endl;
        } else {
            out << convMonth(i) << ": " << avg
                << " kWh/m" << "\u00B2" << std::endl;
        }
    }

    return out.str();
}

std::string Model::handleOption4(const WeatherData& weather_data, int year) const
{
    ostringstream out;

    ofstream ofile("WindTempSolar.csv");
    ofile << year << '\n';

    for (int i = 1; i < 13; ++i) {
        float avgWind = calculateMean(weather_data, i, year, 1);
        float stdDevWind = static_cast<float>(
            calculateStandardDeviation(weather_data, avgWind, i, year, 1)
        );
        float avgRads = calculateMean(weather_data, i, year, 2);
        avgRads = static_cast<float>(convRads(static_cast<int>(avgRads)));
        float stdDevRads = static_cast<float>(
            calculateStandardDeviation(weather_data, avgRads, i, year, 1)
        );
        float avgTemp = calculateMean(weather_data, i, year, 3);

        ofile << convMonth(i) << "," << avgWind << "(" << stdDevWind << "),"
              << avgRads << "(" << stdDevRads << ")," << avgTemp << '\n';
    }

    ofile.close();

    out << "WindTempSolar.csv successfully generated.";
    return out.str();
}

// ---------------- Helper functions ----------------

std::string Model::convMonth(int month) const
{
    static const string monthNames[13]{
        "SKIP", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    return monthNames[month];
}

double Model::convRads(int value) const
{
    // from watts/m2 10mins interval to kWh/m2
    double wattsPerHour = value / 6.0;
    double kiloWattsPerHour = wattsPerHour / 1000.0;

    return kiloWattsPerHour;
}

float Model::calculateMean(const WeatherData& weather_data,
                           int month, int year, int dataType) const
{
    float sum = 0;
    int counter = 0;

    for (int i = 0; i < weather_data.size(); ++i) {
        const WeatherType& rec = weather_data[i];

        if (rec.getDate().getMonth() == month && rec.getDate().getYear() == year) {
            if (dataType == 1) {
                sum += rec.getSpeed();
                ++counter;
            } else if (dataType == 2) {
                if (rec.getSolarRad() >= 100) {
                    sum += rec.getSolarRad();
                    ++counter;
                }
            } else if (dataType == 3) {
                sum += rec.getAirTemp();
                ++counter;
            }
        } else if (rec.getDate().getYear() >= year &&
                   rec.getDate().getMonth() > month) {
            // early escape as per your original logic
            break;
        }
    }

    if (sum != 0 && counter > 0) {
        sum = sum / counter;
        sum = std::round(sum * 10) / 10;
    }

    return sum;
}

double Model::calculateStandardDeviation(const WeatherData& weather_data,
                                         float avg, int month, int year, int dataType) const
{
    double sumSquaredDiff = 0;

    for (int i = 0; i < weather_data.size(); ++i) {
        const WeatherType& rec = weather_data[i];

        if (rec.getDate().getMonth() == month && rec.getDate().getYear() == year) {
            float val = 0.0f;
            if (dataType == 1)      val = rec.getSpeed();
            else if (dataType == 2) val = rec.getSolarRad();
            else if (dataType == 3) val = rec.getAirTemp();

            double diff = val - avg;
            sumSquaredDiff += diff * diff;
        }
    }

    // NOTE: this matches your original logic, even though it uses weather_data.size()
    double variance = sumSquaredDiff / (weather_data.size() - 1);
    double squareRoot = std::sqrt(variance);
    double stdDev = std::round(squareRoot * 10) / 10;

    return stdDev;
}
