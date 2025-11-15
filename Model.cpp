#include "Model.h"
#include <sstream>
#include <cmath>
#include <fstream>

using std::string;
using std::ostringstream;
using std::ofstream;
using std::endl;

std::string Model::handleOption1(const WindlogType& wind_data, int month, int year) const
{
    ostringstream out;

    float avg = std::round(calculateMean(wind_data, month, year, 1) * 36) / 10; // km/h
    float stdDev = static_cast<float>(calculateStandardDeviation(wind_data, avg, month, year, 1));

    if (avg != 0) {
        out << endl << convMonth(month) << " " << year << ":" << endl;
        out << "Average speed: " << avg << " km/h" << endl;
        out << " Sample stdev: " << stdDev;
    } else {
        out << convMonth(month) << " " << year << ": No Data";
    }

    return out.str();
}

std::string Model::handleOption2(const WindlogType& wind_data, int year) const
{
    ostringstream out;

    out << endl << year << endl;

    for (int i = 1; i < 13; ++i) {
        float avg = std::round(calculateMean(wind_data, i, year, 3) * 36) / 10;

        if (avg == 0) {
            out << convMonth(i) << ": No Data" << endl;
        } else {
            out << convMonth(i) << ": average: " << avg
                << " degrees C, stdev: "
                << calculateStandardDeviation(wind_data, avg, i, year, 1) // same as original
                << endl;
        }
    }

    return out.str();
}

std::string Model::handleOption3(const WindlogType& wind_data, int year) const
{
    ostringstream out;

    out << endl << year << endl;

    for (int i = 1; i < 13; ++i) {
        float avg = calculateMean(wind_data, i, year, 2);
        avg = static_cast<float>(convRads(static_cast<int>(avg)));  // same as original signature

        if (avg == 0) {
            out << convMonth(i) << ": No Data" << endl;
        } else {
            out << convMonth(i) << ": " << avg
                << " kWh/m" << "\u00B2" << endl;
        }
    }

    return out.str();
}

std::string Model::handleOption4(const WindlogType& wind_data, int year) const
{
    ostringstream out;

    ofstream ofile("WindTempSolar.csv");
    ofile << year << '\n';

    for (int i = 1; i < 13; ++i) {
        float avgWind = calculateMean(wind_data, i, year, 1);
        float stdDevWind = static_cast<float>(calculateStandardDeviation(wind_data, avgWind, i, year, 1));
        float avgRads = calculateMean(wind_data, i, year, 2);
        avgRads = static_cast<float>(convRads(static_cast<int>(avgRads)));
        float stdDevRads = static_cast<float>(calculateStandardDeviation(wind_data, avgRads, i, year, 1));
        float avgTemp = calculateMean(wind_data, i, year, 3);

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

float Model::calculateMean(const WindlogType& wind_data,
                           int month, int year, int dataType) const
{
    float sum = 0;
    int counter = 0;

    for (int i = 0; i < wind_data.size(); ++i) {
        if (wind_data[i].d.getMonth() == month && wind_data[i].d.getYear() == year) {
            if (dataType == 1) {
                sum += wind_data[i].speed;
                ++counter;
            } else if (dataType == 2) {
                if (wind_data[i].solrad >= 100) {
                    sum += wind_data[i].solrad;
                    ++counter;
                }
            } else if (dataType == 3) {
                sum += wind_data[i].aatemp;
                ++counter;
            }
        } else if (wind_data[i].d.getYear() >= year && wind_data[i].d.getMonth() > month) {
            break;
        }
    }

    if (sum != 0) {
        sum = sum / counter;
        sum = std::round(sum * 10) / 10;
    }

    return sum;
}

double Model::calculateStandardDeviation(const WindlogType& wind_data,
                                         float avg, int month, int year, int dataType) const
{
    double sumSquaredDiff = 0;

    for (int i = 0; i < wind_data.size(); ++i) {
        if (wind_data[i].d.getMonth() == month && wind_data[i].d.getYear() == year) {
            float val = 0.0f;
            if (dataType == 1) val = wind_data[i].speed;
            else if (dataType == 2) val = wind_data[i].solrad;
            else if (dataType == 3) val = wind_data[i].aatemp;

            double diff = val - avg;
            sumSquaredDiff += diff * diff;
        }
    }

    double variance = sumSquaredDiff / (wind_data.size() - 1);
    double squareRoot = std::sqrt(variance);
    double stdDev = std::round(squareRoot * 10) / 10;

    return stdDev;
}
