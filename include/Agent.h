#ifndef PROGRAMA_AGENT_H
#define PROGRAMA_AGENT_H

#include <iostream>

#include "Name.h"
#include "Time.h"
#include "Date.h"
#include "ClientList.h"

using namespace std;

class Agent {
private:
    string code;
    Name name;
    Time startTime;
    Time endTime;
    int extension;
    int extraHours;
    int specialty;
    ClientList* clientList;
public:
    //CONSTRUCTORS
    Agent();
    Agent(const Agent& agent);
    //GETTERS AND SETTERS
    string getCode();
    Name getName();
    Time getStartTime();
    Time getEndTime();
    int getExtension();
    int getExtraHours();
    int getSpecialty();
    ClientList* getClientList();
    void setData(string& code, const Name& name, const Time& startTime, const Time& endTime,
                 int& extension, int& extraHours, int& specialty);
    void setCode(string& code);
    void setName(const Name& name);
    void setStartTime(const Time& startTime);
    void setEndTime(const Time& endTime);
    void setExtension(int& extension);
    void addExtraHours(int& extraHours);
    void setSpecialty(int& specialty);
    void setClientList(ClientList* clientList);
    //returns the agent in string form
    string toString();
    //OPERATORS
    Agent& operator = (const Agent& agent);
    bool operator == (const Agent& agent);
    bool operator != (const Agent& agent);
    bool operator < (const Agent& agent);
    bool operator <= (const Agent& agent);
    bool operator > (const Agent& agent);
    bool operator >= (const Agent& agent);
};


#endif //PROGRAMA_AGENT_H
