#include "Model.h"
#include <sstream>
#include <fstream>
#include <cmath>

using std::string;
using std::ostringstream;
using std::ofstream;
using std::endl;

/// ================== Constructor ====================

/** Constructor */

Model::Model(WeatherMap& map,
             SpeedTree&  sTree,
             TempTree&   tTree,
             SolarTree&  rTree)
    : weather_map(map),
      speedTree(sTree),
      tempTree(tTree),
      solarTree(rTree)
{
}

/// ==================== Option 1 ====================

std::string Model::handleOption1(const WeatherMap& weather_map, int month, int year)  const
{
    ostringstream out;

    WeatherKey key{year, month};
    auto it = weather_map.find(key);
    if (it == weather_map.end() || it->second.speeds.size() == 0) {
        out << convMonth(month) << " " << year << ": No Data";
        return out.str();
    }

    const WeatherMonthlyStats& stats = it->second;
    double meanSpeed_mps = mean(stats.speeds);
    int n = stats.speeds.size();
    if (n < 2) {
        out << convMonth(month) << " " << year << ": No Data";
        return out.str();
    }
    double sdSpeed_mps = sampleStdDev(stats.speeds, meanSpeed_mps);

    /// convert to km/h and round to 1 decimal
    auto round1 = [](double v) {
        return std::round(v * 10.0) / 10.0;
    };

    double meanSpeed_kmh = round1(meanSpeed_mps * 3.6);
    double sdSpeed_kmh   = round1(sdSpeed_mps * 3.6);

    out << endl << convMonth(month) << " " << year << ":" << endl;
    out << "Average speed: " << meanSpeed_kmh << " km/h" << endl;
    out << "Sample stdev: " << sdSpeed_kmh;

    return out.str();
}

/// ==================== Option 2 ====================

std::string Model::handleOption2(const WeatherMap& weather_map,
                                 int year) const
{
    ostringstream out;
    out << endl << year << endl;

    auto round1 = [](double v) {
        return std::round(v * 10.0) / 10.0;
    };

    for (int m = 1; m <= 12; ++m) {
        WeatherKey key{year, m};
        auto it = weather_map.find(key);

        if (it == weather_map.end() || it->second.temps.size() == 0) {
            out << convMonth(m) << ": No Data" << endl;
            continue;
        }

        const WeatherMonthlyStats& stats = it->second;
        int n = stats.temps.size();
        if (n < 2) {
            out << convMonth(m) << ": No Data" << endl;
            continue;
        }

        double meanTemp = mean(stats.temps);
        double sdTemp   = sampleStdDev(stats.temps, meanTemp);

        out << convMonth(m) << ": average: " << round1(meanTemp)
            << " degrees C, stdev: " << round1(sdTemp) << endl;
    }

    return out.str();
}

/// ==================== Option 3 ====================

std::string Model::handleOption3(const WeatherMap& weather_map,
                                 int month) const
{
    ostringstream out;

    /// accumulate across all years for the given month
    Vector<float> allSpeeds;
    Vector<float> allTemps;
    Vector<float> allSolars;

    for (const auto& kv : weather_map) {
        const WeatherKey& key = kv.first;
        if (key.month != month) continue;

        const WeatherMonthlyStats& stats = kv.second;
        int n = stats.speeds.size();

        /// assume speeds, temps, solars all same length for that month/year
        for (int i = 0; i < n; ++i) {
            allSpeeds.insert(stats.speeds[i]);
            allTemps.insert(stats.temps[i]);
            allSolars.insert(stats.solars[i]);
        }
    }

    int nTotal = allSpeeds.size();
    if (nTotal < 2) {
        out << "Sample Pearson Correlation Coefficient for "
            << convMonth(month) << ": No Data";
        return out.str();
    }

    double r_ST = pearsonCorrelation(allSpeeds, allTemps);
    double r_SR = pearsonCorrelation(allSpeeds, allSolars);
    double r_TR = pearsonCorrelation(allTemps, allSolars);

    auto round2 = [](double v) {
        return std::round(v * 100.0) / 100.0;
    };

    out << "Sample Pearson Correlation Coefficient for "
        << convMonth(month) << endl;
    out << "S_T: " << round2(r_ST) << endl;
    out << "S_R: " << round2(r_SR) << endl;
    out << "T_R: " << round2(r_TR);

    return out.str();
}

/// ==================== Option 4 ====================

std::string Model::handleOption4(const WeatherMap& weather_map,
                                 int year) const
{
    ostringstream out;

    ofstream ofile("WindTempSolar.csv");
    if (!ofile.is_open()) {
        out << "Error: could not open WindTempSolar.csv for writing.";
        return out.str();
    }

    ofile << year << '\n';

    auto round1 = [](double v) {
        return std::round(v * 10.0) / 10.0;
    };

    for (int m = 1; m <= 12; ++m) {
        WeatherKey key{year, m};
        auto it = weather_map.find(key);

        if (it == weather_map.end() || it->second.speeds.size() == 0) {

            /// still write a line indicating no data
            ofile << convMonth(m) << ",No Data\n";
            continue;
        }

        const WeatherMonthlyStats& stats = it->second;

        /// --- Wind speed (m/s) -> km/h ---
        double meanSpeed_mps = mean(stats.speeds);
        double sdSpeed_mps   = sampleStdDev(stats.speeds, meanSpeed_mps);
        double madSpeed_mps  = meanAbsoluteDeviation(stats.speeds, meanSpeed_mps);

        double meanSpeed_kmh = round1(meanSpeed_mps * 3.6);
        double sdSpeed_kmh   = round1(sdSpeed_mps * 3.6);
        double madSpeed_kmh  = round1(madSpeed_mps * 3.6);

        /// --- Ambient temperature (deg C) ---
        double meanTemp = mean(stats.temps);
        double sdTemp   = sampleStdDev(stats.temps, meanTemp);
        double madTemp  = meanAbsoluteDeviation(stats.temps, meanTemp);

        meanTemp = round1(meanTemp);
        sdTemp   = round1(sdTemp);
        madTemp  = round1(madTemp);

        /// --- Total solar radiation (kWh/m2) ---
        double totalSolar_kWh = 0.0;
        int n = stats.solars.size();
        for (int i = 0; i < n; ++i) {
            totalSolar_kWh += convRads(stats.solars[i]);
        }
        totalSolar_kWh = round1(totalSolar_kWh);

        /// CSV: Month, avgWind(stdev,mad), avgTemp(stdev,mad), totalSolar
        ofile << convMonth(m) << ","
              << meanSpeed_kmh << "(" << sdSpeed_kmh << "," << madSpeed_kmh << "),"
              << meanTemp      << "(" << sdTemp      << "," << madTemp      << "),"
              << totalSolar_kWh << '\n';
    }

    ofile.close();
    out << "WindTempSolar.csv successfully generated.";

    return out.str();
}

/// ==================== helpers ====================

std::string Model::convMonth(int month) const
{
    static const string monthNames[13]{
        "SKIP", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (month < 1 || month > 12) return "Unknown";
    return monthNames[month];
}

double Model::convRads(double value) const
{
    // Note to self----
    // value is watts/m2 over a 10 minute interval
    // Convert to kWh/m2:
    //  10 minutes = 600 seconds
    //  energy (Wh/m2) = (W/m2 * 600) / 3600 = W/6
    //  kWh/m2 = (W/6) / 1000
    double wattsPerHour = value / 6.0;
    double kiloWattsPerHour = wattsPerHour / 1000.0;
    return kiloWattsPerHour;
}

double Model::mean(const Vector<float>& values) const
{
    int n = values.size();
    if (n == 0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += values[i];
    }
    return sum / n;
}

double Model::sampleStdDev(const Vector<float>& values, double meanVal) const
{
    int n = values.size();
    if (n < 2) return 0.0;

    double sumSq = 0.0;
    for (int i = 0; i < n; ++i) {
        double diff = values[i] - meanVal;
        sumSq += diff * diff;
    }

    double variance = sumSq / (n - 1);
    return std::sqrt(variance);
}

double Model::meanAbsoluteDeviation(const Vector<float>& values,
                                    double meanVal) const
{
    int n = values.size();
    if (n == 0) return 0.0;

    double sumAbs = 0.0;
    for (int i = 0; i < n; ++i) {
        sumAbs += std::fabs(values[i] - meanVal);
    }
    return sumAbs / n;
}

double Model::pearsonCorrelation(const Vector<float>& xs,
                                 const Vector<float>& ys) const
{
    int n = xs.size();
    if (n == 0 || ys.size() != n) return 0.0;
    if (n < 2) return 0.0;

    double sumX = 0.0, sumY = 0.0;
    double sumX2 = 0.0, sumY2 = 0.0;
    double sumXY = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = xs[i];
        double y = ys[i];
        sumX  += x;
        sumY  += y;
        sumX2 += x * x;
        sumY2 += y * y;
        sumXY += x * y;
    }

    double numer = n * sumXY - sumX * sumY;
    double denomPart1 = n * sumX2 - sumX * sumX;
    double denomPart2 = n * sumY2 - sumY * sumY;
    double denom = std::sqrt(denomPart1 * denomPart2);

    if (denom == 0.0) return 0.0;
    return numer / denom;
}
