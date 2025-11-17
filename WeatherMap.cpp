#include "WeatherMap.h"

#include <sstream>
#include <iomanip>


WeatherKey makeWeatherKey(const WeatherType& rec) {
    const Date& d = rec.getDate();
    const Time& t = rec.getTime();

    std::ostringstream os;
    /**
     * setfill to fill the format with 0 to complete the format
     * setw is to dictate the length of the string
     */
    os << std::setfill('0')
       << std::setw(4) << d.getYear()  << '-'
       << std::setw(2) << d.getMonth() << '-'
       << std::setw(2) << d.getDay()   << ' '
       << t.getTime();   /// "HH:MM"

    return os.str();
}
