#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date{
    public:
        /** @brief Constructor */
        Date();
        /**
         * @brief Constructor Overload
         * @param d Integer for Day
         * @param m Integer for Month
         * @param y Integer for Year
         */
        Date(int d, int m, int y);

        /**
         * @brief Getter for day
         * @return Integer resenting Day
         */
        const int getDay() const;
        /**
         * @brief  Getter for month
         * @return Integer resenting Month
         */
        const int getMonth() const;
        /**
         * @brief  Getter for year
         * @return Integer resenting Year YYYY
         */
        const int getYear() const;

        /**
         * @brief Setter for mark
         * @param d Integer for Day
         */
        void setDay(int d);
        /**
         * @brief Setter for mark
         * @param d Integer for Month
         */
        void setMonth(int m);
        /**
         * @brief Setter for mark
         * @param d Integer for Year YYYY
         */
        void setYear(int y);

        /**
         * @brief Comparison operator < for ordering by (year, month, day)
         * @param other Another Date class to make the comparison
         */
        bool operator<(const Date& other) const;
        /**
         * @brief Comparison operator == for ordering by (year, month, day)
         * @param other Another Date class to make the comparison
         */
        bool operator==(const Date& other) const;

    private:
        /** @brief Day of the month */
        int day;
        /** @brief Month of the year */
        int month;
        /** @brief Year */
        int year;
};



#endif
