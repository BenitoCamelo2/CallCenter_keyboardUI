#ifndef PROGRAMA_CLIENTNODE_H
#define PROGRAMA_CLIENTNODE_H

#include <iostream>

#include "Client.h"

class ClientNode {
private:
    //data and node
    Client data;
    ClientNode* next;
public:
    //CONSTRUCTORS
    ClientNode();
    ClientNode(const Client& client);
    //GETTERS AND SETTERS
    Client getData();
    ClientNode* getNext();
    void setData(const Client& client);
    void setNext(ClientNode* clientNode);
};


#endif //PROGRAMA_CLIENTNODE_H
