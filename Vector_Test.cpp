#include "Vector.h"
#include "Date.h"
#include <string>


using namespace std;

typedef struct {
    int integer;
    string str;
    Date d;
} VectorRecord;

typedef Vector<VectorRecord> VectorData;

void setUp(VectorData& testMyVector);

//int main()
int commentThisOutAndUseMain_Vector()
{
    VectorData testMyVector;
    setUp(testMyVector);
    return 0;
}

void setUp(VectorData& testMyVector) {

    Date d(4, 3, 2021);
    VectorRecord record = {69,"My Vector",d};
    //testMyVector.append(record);

    //-------------------------
    cout << "Test Default Constructor (size = 1)" << endl
    << testMyVector.size() << endl;


    testMyVector.append(record);

    //-------------------------
    cout << "Test Appending 1 item (size)" << endl
    << testMyVector.size() << endl;


    testMyVector.append(record);

    //-------------------------
    cout << "Test Appending 2 item (size)" << endl
    << testMyVector.size() << endl;


    testMyVector.append(record);

    //-------------------------
    cout << "Test Accessing Records ( int type )" << endl
    << testMyVector[0].integer << endl;

    //-------------------------
    cout << "Test Accessing Records ( string type )" << endl
    << testMyVector[0].str << endl;

    //-------------------------
    cout << "Test Accessing Records ( Date.getMonth() )" << endl
    << testMyVector[0].d.getMonth() << endl;
}
