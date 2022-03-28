#include "../include/Time.h"

bool Time::isValid(const int &h, const int &m) {
    return h < 24 && h >= 0 && m < 60 && m >= 0;
}

int Time::toInt() const {
    return hour * 100 + minute;
}

//default constructor sets the time to the system time
Time::Time() {
    chrono::system_clock::time_point today = chrono::system_clock::now();
    time_t tt;
    tt = chrono::system_clock::to_time_t (today);
    struct tm* timeinfo;
    timeinfo = localtime(&tt);

    hour = timeinfo->tm_hour;
    minute = timeinfo->tm_min;
}

Time::Time(const int &h, const int &m) :Time(){
    if(isValid(h, m)) {
        hour = h;
        minute = m;
    }
}

int Time::getHour() {
    return hour;
}

int Time::getMinute() {
    return minute;
}

bool Time::setData(const int &h, const int &m) {
    if(h < 24 && h >= 0 && m < 60 && m >= 0){
        hour = h;
        minute = m;
        return true;
    } else {
        return false;
    }
}

string Time::toString() {
    string result;
    if(hour <= 9){
        result += "0";
    }
    result += to_string(hour);
    result += ":";
    if(minute <= 9){
        result += "0";
    }
    result += to_string(minute);
    return result;
}

Time &Time::operator = (const Time &t) {
    hour = t.hour;
    minute = t.minute;

    return *this;
}

bool Time::operator == (const Time &t) const {
    return toInt() == t.toInt();
}

bool Time::operator != (const Time &t) const {
    return toInt() != t.toInt();
}

bool Time::operator < (const Time &t) const {
    return toInt() < t.toInt();
}

bool Time::operator <= (const Time &t) const {
    return toInt() <= t.toInt();
}

bool Time::operator > (const Time &t) const {
    return toInt() > t.toInt();
}

bool Time::operator >= (const Time &t) const {
    return toInt() >= t.toInt();
}
