#include "../include/Agent.h"

Agent::Agent() {
    code = "";
    name = Name();
    endTime = Time();
    startTime = Time();
    extension = 0;
    extraHours = 0;
    specialty = 0;
    clientList = new ClientList();
}

Agent::Agent(const Agent &agent) {
    this->code = agent.code;
    this->name = agent.name;
    this->startTime = agent.startTime;
    this->endTime = agent.endTime;
    this->extension = agent.extension;
    this->extraHours = agent.extraHours;
    this->specialty = agent.specialty;
    this->clientList = agent.clientList;
}

string Agent::getCode() {
    return code;
}

Name Agent::getName() {
    return name;
}

Time Agent::getStartTime() {
    return startTime;
}

Time Agent::getEndTime() {
    return endTime;
}

int Agent::getExtension() {
    return extension;
}

int Agent::getExtraHours() {
    return extraHours;
}

int Agent::getSpecialty() {
    return specialty;
}

ClientList* Agent::getClientList() {
    return clientList;
}

void Agent::setData(string &code, const Name &name, const Time &startTime, const Time &endTime, int &extension,
                    int &extraHours, int &specialty) {
    this->code = code;
    this->name = name;
    this->startTime = startTime;
    this->endTime = endTime;
    this->extension = extension;
    this->extraHours = extraHours;
    this->specialty = specialty;
}

void Agent::setCode(string& code){
    this->code = code;
}

void Agent::setName(const Name &name) {
    this->name = name;
}

void Agent::setStartTime(const Time &startTime) {
    this->startTime = startTime;
}

void Agent::setEndTime(const Time &endTime) {
    this->endTime = endTime;
}

void Agent::setExtension(int& extension) {
    this->extension = extension;
}

void Agent::setSpecialty(int &specialty) {
    this->specialty = specialty;
}

void Agent::addExtraHours(int &extraHours) {
    this->extraHours += extraHours;
}

void Agent::setClientList(ClientList *clientList) {
    this->clientList = clientList;
}

Agent &Agent::operator=(const Agent &agent) {
    extension = agent.extension;
    code = agent.code;
    name = agent.name;
    startTime = agent.startTime;
    endTime = agent.endTime;
    extraHours = agent.extraHours;
    specialty = agent.specialty;
    clientList = agent.clientList;

    return *this;
}

string Agent::toString() {
    string result;

    result = code;
    result += "|";
    result += name.toString();
    result += "|";
    result += startTime.toString();
    result += "|";
    result += endTime.toString();
    result += "|";
    result += to_string(extension);
    result += "|";
    result += to_string(extraHours);
    result += "|";
    result += to_string(specialty);
    result += "|";

    return result;
}

bool Agent::operator==(const Agent &agent) {
    return code == agent.code;
}

bool Agent::operator!=(const Agent &agent) {
    return code != agent.code;
}

bool Agent::operator<(const Agent &agent) {
    return code < agent.code;
}

bool Agent::operator<=(const Agent &agent) {
    return code <= agent.code;
}

bool Agent::operator>(const Agent &agent) {
    return code > agent.code;
}

bool Agent::operator>=(const Agent &agent) {
    return code >= agent.code;
}
