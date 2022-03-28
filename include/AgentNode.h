#ifndef PROGRAMA_AGENTNODE_H
#define PROGRAMA_AGENTNODE_H

#include <iostream>

#include "Agent.h"

using namespace std;

class AgentNode {
private:
    //data and nodes
    Agent* dataPTR;
    AgentNode* prev;
    AgentNode* next;
public:
    //CONSTRUCTORS
    AgentNode();
    AgentNode(const Agent& agent);
    ~AgentNode();

    //SETTERS AND GETTERS
    Agent* getDataPtr();
    Agent getData();
    AgentNode* getPrev();
    AgentNode* getNext();
    void setDataPtr(Agent* agent);
    void setData(const Agent& agent);
    void setPrev(AgentNode* agentNode);
    void setNext(AgentNode* agentNode);
};


#endif //PROGRAMA_AGENTNODE_H
