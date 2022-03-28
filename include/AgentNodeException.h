#ifndef PROGRAMA_AGENTNODEEXCEPTION_H
#define PROGRAMA_AGENTNODEEXCEPTION_H

#include <iostream>

using namespace std;

class AgentNodeException {
private:
    string msg;
public:
    AgentNodeException(const char message);
    AgentNodeException(const string message);
    ~AgentNodeException();
    const char* what();
};


#endif //PROGRAMA_AGENTNODEEXCEPTION_H
