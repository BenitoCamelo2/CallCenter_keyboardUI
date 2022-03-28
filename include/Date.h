#ifndef PROGRAMA_DATE_H
#define PROGRAMA_DATE_H

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

class Date {
private:
    //data and makes sure the date is valid
    int year, month, day;
    bool isValid(const int& y, const int& m, const int& d);
    int toInt();
public:
    //CONSTRUCTORS
    Date();
    Date(const int& y, const int& m, const int& d);
    //GETTERS AND SETTERS
    int getYear();
    int getMonth();
    int getDay();
    bool setData(const int& y, const int& m, const int& d);
    //returns the date in DD/MM/YYYY form
    string toString();
    //OPERATORS
    Date& operator = (const Date& date);
    bool operator == (Date& date);
    bool operator != (Date& date);
    bool operator < (Date& date);
    bool operator <= (Date& date);
    bool operator > (Date& date);
    bool operator >= (Date& date);
};


#endif //PROGRAMA_DATE_H
