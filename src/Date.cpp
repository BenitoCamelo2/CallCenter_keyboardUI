#include "../include/Date.h"


//makes sure date is valid
bool Date::isValid(const int &y, const int &m, const int &d) {
    if(m < 1 || m > 12){
        return false;
    }
    if(d < 1 || d > 31){
        return false;
    }
    if(m == 2){
        if(((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)){
            return(d <= 29);
        } else {
            return(d <= 28);
        }
    }
    if(m == 4 || m == 6 || m == 9 || m == 11){
        return(d <= 30);
    }
    return true;
}

int Date::toInt() {
    return (year%100) + 100 * month + 10000 * day;
}

//sets the date and time to the system time
Date::Date() {
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    year = 1900 + local_tm.tm_year;
    month = 1 + local_tm.tm_mon;
    day = local_tm.tm_mday;
}

//sets the day, month and year
Date::Date(const int &y, const int &m, const int &d) :Date(){
    if(isValid(y, m, d)){
        year = y;
        month = m;
        day = d;
    }
}

int Date::getYear() {
    return year;
}

int Date::getMonth() {
    return month;
}

int Date::getDay() {
    return day;
}

bool Date::setData(const int &y, const int &m, const int &d) {
    if(isValid(y, m, d)){
        year = y;
        month = m;
        day = d;
        return true;
    } else {
        return false;
    }
}

string Date::toString() {
    string result;
    result = to_string(day);
    result += "/";
    result += to_string(month);
    result += "/";
    result += to_string(year);

    return result;
}

Date &Date::operator=(const Date &date) {
    year = date.year;
    month = date.month;
    day = date.day;
    
    return *this;
}

bool Date::operator==(Date &date) {
    return toString() == date.toString();
}

bool Date::operator!=(Date &date) {
    return toString() != date.toString();
}

bool Date::operator<(Date &date) {
    return toString() < date.toString();
}

bool Date::operator<=(Date &date) {
    return toString() <= date.toString();
}

bool Date::operator>(Date &date) {
    return toString() > date.toString();
}

bool Date::operator>=(Date &date) {
    return toString() >= date.toString();
}
