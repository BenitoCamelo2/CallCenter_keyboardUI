#ifndef PROGRAMA_AGENTLIST_H
#define PROGRAMA_AGENTLIST_H

#include <iostream>
#include "AgentNode.h"

using namespace std;

class AgentList {
private:
    AgentNode* header;
    bool isValidPos(AgentNode* agent);
    void copyAll(const AgentList &agentList);
    void swapPtr(AgentNode* agent1, AgentNode* agent2);
    void sortByName(AgentNode* agent1, AgentNode* agent2);
    void sortBySpecialty(AgentNode* agent1, AgentNode* agent2);
public:
    //CONSTRUCTORS
    AgentList();
    ~AgentList();

    //returns if the list is empty or not
    bool isEmpty();
    //inserts data, not ordered
    void insertData(AgentNode* agentNode, const Agent& tempAgent);
    //delets data
    void deleteData(AgentNode* agentNode);
    //returns the header
    AgentNode* getFirstPos();
    //returns the last node in the list
    AgentNode* getLastPos();
    //returns the previous position in the list
    AgentNode* getPrevPos(AgentNode* agentNode);
    //returns the next position in the list
    AgentNode* getNextPos(AgentNode* agentNode);
    //finds the position of an agent, based on a search option
    AgentNode* findData(Agent& agent, int option);
    //gets the agend data based off of a position
    Agent retrieve(AgentNode* agentNode);
    //sorts
    void sortByName();
    void sortBySpecialty();
    //returns the list in string form
    string toString();
    //delets all agents
    void deleteAll();
    //read-write to disk
    void writeToDisk(const string& data);
    string readFromDisk();
};


#endif //PROGRAMA_AGENTLIST_H
