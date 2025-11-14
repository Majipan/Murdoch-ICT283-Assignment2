#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

using std::string;

class Time{
    public:
        /** Constructor */
        Time();
        /** Constructor Overload */
        Time(string h, string m);
        /** Getter for Time */
        const string getTime() const;

        /** Set Hours */
        void setHour(string h);
        /** Set Minutes */
        void setMins(string m);


    private:
        string hour;
        string mins;
};

#endif // TIME_H
