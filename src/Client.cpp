#include "../include/Client.h"

Client::Client() {
    phoneNumber = "";
    callStart = Time();
    callDuration = Time();
    callDate = Date();
}

Client::Client(const long long &phoneNumber, const Time &callStart, const Time &callDuration, const Date &callDate) {
    this->phoneNumber = phoneNumber;
    this->callStart = callStart;
    this->callDuration = callDuration;
    this->callDate = callDate;
}

string Client::getPhoneNumber() {
    return phoneNumber;
}

Time Client::getCallStart() {
    return callStart;
}

Time Client::getCallDuration() {
    return callDuration;
}

Date Client::getCallDate() {
    return callDate;
}

void Client::setData(const string &phoneNumber, const Time &callStart, const Time &callDuration, const Date &callDate) {
    this->phoneNumber = phoneNumber;
    this->callStart = callStart;
    this->callDuration = callDuration;
    this->callDate = callDate;
}

void Client::setPhoneNumber(const string &phoneNumber) {
    this->phoneNumber = phoneNumber;
}

void Client::setCallStart(const Time &callStart) {
    this->callStart = callStart;
}

void Client::setCallDuration(const Time &callDuration) {
    this->callDuration = callDuration;
}

void Client::setCallDate(const Date &callDate) {
    this->callDate = callDate;
}

string Client::toString(){
    string result;

    result = phoneNumber;
    result += " | ";
    result += callStart.toString();
    result += " | ";
    result += callDuration.toString();
    result += " | ";
    result += callDate.toString();

    return result;

}

Client &Client::operator = (const Client &client) {
    phoneNumber = client.phoneNumber;
    callStart = client.callStart;
    callDuration = client.callDuration;
    callDate = client.callDate;

    return *this;
}

bool Client::operator == (const Client &client) {
    return phoneNumber == client.phoneNumber;
}

bool Client::operator != (const Client &client) {
    return phoneNumber != client.phoneNumber;
}

bool Client::operator < (const Client &client) {
    return phoneNumber < client.phoneNumber;
}

bool Client::operator <= (const Client &client) {
    return phoneNumber <= client.phoneNumber;
}

bool Client::operator > (const Client &client) {
    return phoneNumber > client.phoneNumber;
}

bool Client::operator >= (const Client &client) {
    return phoneNumber >= client.phoneNumber;
}
