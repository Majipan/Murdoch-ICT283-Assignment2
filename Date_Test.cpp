#include "Date.h"

void setUp(Date dateDefault, Date date);

using namespace std;

//int main()
int commentThisOutAndUseMain_Date()
{
    Date dateDefault;               // Test default constructor
    Date date(1,2,2034);
    setUp(dateDefault, date);
    return 0;
}

void setUp(Date dateDefault, Date date) {
    //-------------------------
    cout << "Test Default Constructor" << endl
    << dateDefault.getDay() << "/"
    << dateDefault.getMonth() << "/"
    << dateDefault.getYear() << endl;

    //-------------------------
    cout << "Test Constructor Overload" << endl
    << date.getDay() << "/"
    << date.getMonth() << "/"
    << date.getYear() << endl;

    //-------------------------
    date.setDay(8);
    cout << "Test Day Setter" << endl
    << date.getDay() << endl;

    //-------------------------
    date.setMonth(8);
    cout << "Test Month Setter" << endl
    << date.getMonth() << endl;

    //-------------------------
    date.setYear(2018);
    cout << "Test Year Setter" << endl
    << date.getYear() << endl;
}
