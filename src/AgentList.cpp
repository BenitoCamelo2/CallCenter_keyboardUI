#include "../include/AgentList.h"
#include "../include/ListException.h"
#include "../include/AgentMenu.h"
#include "../include/util.h"

bool AgentList::isValidPos(AgentNode *agentNode) {
    AgentNode* temp(header);

    while(temp != nullptr){
        //if agent is found the position is valid
        if(temp == agentNode){
            return true;
        }
        temp = getNextPos(temp);
    }
    //in this case the agent is not in the list
    return false;
}

void AgentList::copyAll(const AgentList &agentList) {

}

void AgentList::swapPtr(AgentNode *agent1, AgentNode *agent2) {

}

void AgentList::sortByName(AgentNode *agent1, AgentNode *agent2) {

}

void AgentList::sortBySpecialty(AgentNode *agent1, AgentNode *agent2) {

}

AgentList::AgentList() : header(nullptr){}

AgentList::~AgentList() {
    deleteAll();
    delete header;
}

bool AgentList::isEmpty() {
    return header == nullptr;
}

void AgentList::insertData(AgentNode *agentNode, const Agent &tempAgent) {
    //position is invalid, will try to insert
    if(agentNode != nullptr && !isValidPos(agentNode)){
        throw ListException("Posicion invalida, tratando de insertar");
    }

    //first node to add to the list
    if(agentNode == nullptr){
        agentNode = header;
    }

    //temp node using the agent in the parameter as the data
    AgentNode* newOne(new AgentNode(tempAgent));

    //no more memory
    if(newOne == nullptr){
        throw ListException("Memoria no disponible, tratando de insertar");
    }

    //setters
    newOne->setNext(header);
    newOne->setPrev(nullptr);

    //if header is not the only item in the list
    if(header!=nullptr){
        header->setPrev(newOne);
    }
    header = newOne;
}

void AgentList::deleteData(AgentNode *agentNode) {
    AgentNode* temp(header);

    //if the agent wasn't found
    if(agentNode == nullptr){
        throw ListException("No existe el agente");
        return;
    //no elements in the list
    } else if(temp == nullptr){
        throw ListException("No hay agentes en la lista");
        return;
    }
    //if the element is the header
    if(temp == agentNode){
        header = header->getNext();
        free(agentNode);
        return;
    }
    //if the element is the last in the list
    if(agentNode == getLastPos()){
        temp = agentNode;
        temp = temp->getPrev();
        temp->setNext(nullptr);
        free(agentNode);
        return;
    }
    //when the node has a prev and next that are not nullptr, so in between two nodes
    if(agentNode != header && agentNode != getLastPos()) {
        while (temp != agentNode) {
            temp = getNextPos(temp);
        }
        if (temp == agentNode) {
            temp->getNext()->setPrev(temp->getPrev());
            temp->getPrev()->setNext(temp->getNext());
            free(agentNode);
        }
    }


}

AgentNode *AgentList::getFirstPos() {
    if(!isEmpty()){
        return header;
    } else {
        return nullptr;
    }
}

AgentNode *AgentList::getLastPos() {
    if(!isEmpty()) {
        AgentNode *temp;
        temp = header;
        while (temp != nullptr) {
            if(getNextPos(temp) == nullptr){
                return temp;
            } else {
                temp = getNextPos(temp);
            }
        }

    } else {
        return nullptr;
    }
    return nullptr;
}

AgentNode *AgentList::getPrevPos(AgentNode* agentNode) {
    return agentNode->getPrev();
}

AgentNode *AgentList::getNextPos(AgentNode* agentNode) {
    return agentNode->getNext();
}

AgentNode *AgentList::findData(Agent &agent, int option) {
    AgentNode* temp(header);

    //switch for what attribute to search by
    switch(option){
        //searching by code
        case SEARCH_CODE : {
            //basic way to traverse list
            while(temp != nullptr){
                if(temp->getData() == agent){
                    //if found returns the node in the list
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            //if not found returns nullptr
            return nullptr;
        }
        //searching by name
        case SEARCH_LAST_NAME: {
            //all of the cases use the same search method
            while(temp != nullptr){
                if(temp->getData().getName().getLastName() == agent.getName().getLastName()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by shift start time
        case SEARCH_HOUR_START: {
            while(temp != nullptr){
                if(temp->getData().getStartTime().getHour() == agent.getStartTime().getHour()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by shift end time
        case SEARCH_HOUR_END: {
            while(temp != nullptr){
                if(temp->getData().getEndTime().getHour() == agent.getEndTime().getHour()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by extension
        case SEARCH_EXTENSION: {
            while(temp != nullptr){
                if(temp->getData().getExtension() == agent.getExtension()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //search by specialty, should improve to show all agents with the same specialty
        case SEARCH_SPECIALTY: {
            while(temp != nullptr){
                if(temp->getData().getSpecialty() == agent.getSpecialty()){
                    return temp;
                } else {
                    temp = getNextPos(temp);
                }
            }
            return nullptr;
        }
        //shouldn't happen, would be unfortunate
        default: {
            cout << "Error al buscar agente" << endl;
            cin.ignore();
            cout << "Ingresa una tecla para continuar..." << endl;
            getchar();
        }
    }
    return nullptr;
}

Agent AgentList::retrieve(AgentNode *agentNode) {
    //searches through the list
    //could use the isValidPos(), but it returns a blank agent if node is not found, so its the same thing
    AgentNode* temp(header);
    while(temp != nullptr){
        if(temp == agentNode){
            return temp->getData();
        } else {
            temp = getNextPos(temp);
        }
    }
    return {};
}

void AgentList::sortByName() {

}

void AgentList::sortBySpecialty() {

}

string AgentList::toString() {
    AgentNode* temp(header);
    string result;

    while(temp != nullptr){
        result += temp->getData().toString();
        result += "\n";

        temp = getNextPos(temp);
    }
    return result;
}

void AgentList::deleteAll() {
    //deletes all while going through the list, temp gets the next element and prev deletes the previous element
    AgentNode* temp(header);
    AgentNode* prev;
    while(temp != nullptr){
        prev = temp;
        temp = getNextPos(temp);
        delete prev;
    }
    header = nullptr;
}

void AgentList::writeToDisk(const string &data) {

}

string AgentList::readFromDisk() {
    return "";
}
