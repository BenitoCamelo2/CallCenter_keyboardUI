#ifndef PROGRAMA_CLIENT_H
#define PROGRAMA_CLIENT_H

#include <iostream>

#include "Time.h"
#include "Date.h"
#include "util.h"

using namespace std;

class Client {
private:
    //client attributes
    string phoneNumber;
    Time callDuration;
    Time callStart;
    Date callDate;
public:
    //CONSTRUCTORS
    Client();
    Client(const long long& phoneNumber, const Time& callStart, const Time& callDuration, const Date& callDate);
    //GETTERS AND SETTERS
    string getPhoneNumber();
    Time getCallStart();
    Time getCallDuration();
    Date getCallDate();
    void setData(const string& phoneNumber, const Time& callStart, const Time& callDuration, const Date& callDate);
    void setPhoneNumber(const string& phoneNumber);
    void setCallStart(const Time& callStart);
    void setCallDuration(const Time& callDuration);
    void setCallDate(const Date& callDate);
    //returns a string of the client data separated by |
    string toString();
    //OPERATORS
    Client& operator = (const Client& client);
    bool operator == (const Client& client);
    bool operator != (const Client& client);
    bool operator < (const Client& client);
    bool operator <= (const Client& client);
    bool operator > (const Client& client);
    bool operator >= (const Client& client);
};


#endif //PROGRAMA_CLIENT_H
