#include <iostream>
#include <time.h>

using namespace std;

class Date
{
    int day;
    int month;
    int year;

public:

    Date();
    Date(int, int, int);
    Date(Date&);
    ~Date();
    inline int getDay() const;
    inline int getMonth() const;
    inline int getYear() const;
    Date& setDay(int);
    Date& setMonth(int);
    Date& setYear(int);
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    void print() const;
};