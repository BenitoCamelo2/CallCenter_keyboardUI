#ifndef PROGRAMA_LISTEXCEPTION_H
#define PROGRAMA_LISTEXCEPTION_H

#include <iostream>

using namespace std;

class ListException {
private:
    string msg;
public:
    explicit ListException(const char* message) : msg(message){}
    explicit ListException(const string message) : msg(message){}
    virtual ~ListException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};


#endif //PROGRAMA_LISTEXCEPTION_H
