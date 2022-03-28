#ifndef PROGRAMA_NAME_H
#define PROGRAMA_NAME_H

#include <iostream>

using namespace std;

class Name {
private:
    //first and last name
    string firstName;
    string lastName;
public:
    //CONSTRUCTORS
    Name();
    Name(string fname, string lname);
    //GETTERS AND SETTERS
    string getFirstName();
    string getLastName();
    void setData(const string& fname, const string& lname);
    //returns "firstName lastName"
    string toString();
    //OPERATORS
    Name& operator = (const Name& name);
    bool operator == (const Name& name);
    bool operator != (const Name& name);
    bool operator < (const Name& name);
    bool operator <= (const Name& name);
    bool operator > (const Name& name);
    bool operator >= (const Name& name);
};


#endif //PROGRAMA_NAME_H
