#include "../include/ClientNode.h"

ClientNode::ClientNode() {
    data = Client();
    next = nullptr;
}

ClientNode::ClientNode(const Client &client) {
    data = client;
    next = nullptr;
}

Client ClientNode::getData() {
    return data;
}

ClientNode *ClientNode::getNext() {
    return next;
}

void ClientNode::setData(const Client &client) {
    data = client;
}

void ClientNode::setNext(ClientNode *clientNode) {
    next = clientNode;
}
