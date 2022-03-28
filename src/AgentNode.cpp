#include "../include/AgentNode.h"

AgentNode::AgentNode() : dataPTR(nullptr), prev(nullptr), next(nullptr){}

AgentNode::AgentNode(const Agent &agent) : dataPTR(new Agent(agent)), prev(nullptr), next(nullptr){}

AgentNode::~AgentNode() {
    delete dataPTR;
}

Agent* AgentNode::getDataPtr() {
    if(dataPTR == nullptr){
        return nullptr;
    } else {
        return dataPTR;
    }
}

Agent AgentNode::getData() {
    return *dataPTR;
}

AgentNode *AgentNode::getPrev() {
    return prev;
}

AgentNode *AgentNode::getNext() {
    return next;
}

void AgentNode::setDataPtr(Agent* agent){
    dataPTR = agent;
}

void AgentNode::setData(const Agent &agent) {
    delete dataPTR;
    dataPTR = new Agent(agent);
}

void AgentNode::setPrev(AgentNode *agentNode) {
    prev = agentNode;
}

void AgentNode::setNext(AgentNode *agentNode) {
    next = agentNode;
}
