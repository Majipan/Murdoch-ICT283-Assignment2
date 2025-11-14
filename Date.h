#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date{
    public:
        /** Constructor */
        Date();
        Date(int d, int m, int y);

        /** Getter for day */
        int getDay() const;
        /** Getter for month */
        int getMonth() const;
        /** Getter for year */
        int getYear() const;

        /** Getter for full date */
        //std::string getFullDate() const;

        /** Setter for mark */
        void setDay(int d);
        /** Setter for mark */
        void setMonth(int m);
        /** Setter for mark */
        void setYear(int y);

    private:
        /** Day of the month */
        int day;
        /** Month of the year */
        int month;
        /** Year */
        int year;
};

#endif
