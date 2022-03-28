#ifndef PROGRAMA_TIME_H
#define PROGRAMA_TIME_H

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class Time {
private:
    //data and time validater
    int hour, minute;
    bool isValid(const int& h, const int& m);
public:
    //CONSTRUCTORS
    Time();
    Time(const int& h, const int& m);
    //converts to int
    int toInt() const;
    //GETTERS AND SETTERS
    int getHour();
    int getMinute();
    bool setData(const int& hour, const int& minute);
    //returns time in HH:MM form, even 2:8 is displayed as 02:08
    string toString();
    //OPERATORS
    Time& operator = (const Time& t);
    bool operator == (const Time& t) const;
    bool operator != (const Time& t) const;
    bool operator < (const Time& t) const;
    bool operator <= (const Time& t) const;
    bool operator > (const Time& t) const;
    bool operator >= (const Time& t) const;
};


#endif //PROGRAMA_TIME_H
