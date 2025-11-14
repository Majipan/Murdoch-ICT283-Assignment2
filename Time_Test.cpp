#include "Time.h"

void setUp(Time dateDefault, Time date);

using namespace std;

//int main()
int commentThisOutAndUseMain_Time()
{
    Time timeDefault;               // Test default constructor
    Time time("11", "30");
    setUp(timeDefault, time);
    return 0;
}

void setUp(Time timeDefault, Time time) {
    //-------------------------
    cout << "Test Default Constructor" << endl
    << timeDefault.getTime() << endl;

    //-------------------------
    cout << "Test Constructor Overload" << endl
    << time.getTime() << endl;

    //-------------------------
    time.setHour("04");
    cout << "Test Hour Setter" << endl
    << time.getTime() << endl;

    //-------------------------
    time.setMins("04");
    cout << "Test Mins Setter" << endl
    << time.getTime() << endl;
}
