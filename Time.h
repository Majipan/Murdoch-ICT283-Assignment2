#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>

class Time{
    public:
        /** @brief Constructor */
        Time();
        /**
         * @brief Constructor Overload
         * @param h Hours
         * @param m Minutes
         */
        Time(int h, int m);

        /**
         * @brief Getter for Time
         * @return string For the Hours and Minutes HH:MM
         */
        const std::string getTime() const;

        /**
         * @brief Get Hours
         * @return Integer for hours not yet formatted for 2 digits
         */
        const int getHour() const;
        /**
         * @brief Get Mins
         * @return Integer for mins not yet formatted for 2 digits
         */
        const int getMins() const;

        /**
         * @brief Set Hours
         * @param h Hour in HH
         */
        void setHour(int h);
        /**
         * @brief Set Minutes
         * @param m Minutes in MM
         */
        void setMins(int m);

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
        int hour;
        int mins;
};

#endif // TIME_H
