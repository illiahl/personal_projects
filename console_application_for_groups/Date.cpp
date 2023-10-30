#include "Date.h"

Date::Date()
{
    int seconds;
    
    time_t timer;
    timer = time(NULL);

    struct tm beginningof2022 = {0};
    beginningof2022.tm_hour = 0;   beginningof2022.tm_min = 0; beginningof2022.tm_sec = 0;
    beginningof2022.tm_year = 122; beginningof2022.tm_mon = 0; beginningof2022.tm_mday = 1;

    seconds = difftime(timer,mktime(&beginningof2022));

    month = ((seconds*12)/(3600*24*365) + 1) % 13;
    year = 2022 + seconds/(3600*24*365);
    day = seconds/(3600*24);

    for (int i = 1; i < month + 12*(year - 2022); i++){
        if(i%13 <= 7 && i%2 == 1 && !(i == 2 || (i > 12 && i%13 == 2 && (2022 + i/12)%4 != 0))) day = day - 31;
        else if(i%13 <= 7 && i%2 == 0 && !(i == 2 || (i > 12 && i%13 == 2 && (2022 + i/12)%4 != 0))) day = day - 30;
        else if(i%13 > 7 && i%2 == 1 && !(i == 2 || (i > 12 && i%13 == 2 && (2022 + i/12)%4 != 0))) day = day - 30;
        else if(i%13 > 7 && i%2 == 0 && !(i == 2 || (i > 12 && i%13 == 2 && (2022 + i/12)%4 != 0))) day = day - 31;
        else if (i == 2 || (i > 12 && i%13 == 2 && (2022 + i/12)%4 != 0)) day = day - 28;
        else day = day - 29;
    }
    day += 1;
}

Date::Date(int d, int m, int y)
{
    if (d >= 0 && m >= 0 && y >= 0){
        day = d;
        month = m;
        year = y;
    }
    else{
        cout << "Invalid input data!" << endl;
        exit(0);
    }
}

Date::Date(Date& date1)
{
    day = date1.day;
    month = date1.month;
    year = date1.year;
}

Date::~Date() {}

inline int Date::getDay() const
{
    return day;
}

inline int Date::getMonth() const
{
    return month;
}

inline int Date::getYear() const
{
    return year;
}

Date& Date::setDay(int d)
{
    if (d >= 0) day = d;
    else{
        cout << "Invalid input data!" << endl;
        exit(0);
    }
}

Date& Date::setMonth(int m)
{
    if (m >= 0) month = m;
    else{
        cout << "Invalid input data!" << endl;
        exit(0);
    }
}

Date& Date::setYear(int y)
{
    if (y >= 0) year = y;
    else{
        cout << "Invalid input data!" << endl;
        exit(0);
    }
}

Date& Date::operator++()
{
    day++;
    return *this;
}

Date Date::operator++(int)
{
    Date temp(*this);
    day++;
    return temp;
}

Date& Date::operator--()
{
    day--;
    return *this;
}

Date Date::operator--(int)
{
    Date temp(*this);
    day--;
    return temp;
}

void Date::print() const
{
    if (day < 10){
        if(month < 10) cout << "0" << day << ".0" << month << "." << year << endl;
        else cout << "0" << day << "." << month << "." << year << endl;
    }
    else{
        if (month < 10) cout << day << ".0" << month << "." << year << endl;
        else cout << day << "." << month << "." << year << endl;
    }
}