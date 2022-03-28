#include "../include/AgentNodeException.h"

AgentNodeException::AgentNodeException(const char message) {

}

AgentNodeException::AgentNodeException(const string message) {

}

AgentNodeException::~AgentNodeException() {

}

const char *AgentNodeException::what() {
    return nullptr;
}
