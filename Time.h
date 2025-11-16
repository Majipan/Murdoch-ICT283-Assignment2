#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

using std::string;

class Time{
    public:
        /** @brief Constructor */
        Time();
        /**
         * @brief Constructor Overload
         * @param h Hours
         * @param m Minutes
         */
        Time(string h, string m);

        /**
         * @brief Getter for Time
         * @return string For the Hours and Minutes HH:MM
         */
        const string getTime() const;

        /**
         * @brief Set Hours
         * @param h Hour in HH
         */
        void setHour(string h);
        /**
         * @brief Set Minutes
         * @param m Minutes in MM
         */
        void setMins(string m);

        /**
         * @brief Comparison operator < for ordering by (hour, minute)
         * @param other Time class to make the comparison
         */
        bool operator<(const Time& other) const;
        /**
         * @brief Comparison operator == for ordering by (hour, minute)
         * @param other Time class to make the comparison
         */
        bool operator==(const Time& other) const;


    private:
        string hour;
        string mins;
};

#endif // TIME_H
