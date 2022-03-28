#include "../include/Name.h"

Name::Name() {
    firstName = "Nombre";
    lastName = "Apellido";
}

Name::Name(string fname, string lname) {
    firstName = fname;
    lastName = lname;
}

string Name::getFirstName() {
    return firstName;
}

string Name::getLastName() {
    return lastName;
}

void Name::setData(const string &fname, const string &lname) {
    firstName = fname;
    lastName = lname;
}

string Name::toString() {
    string result;
    result += firstName;
    result += " ";
    result += lastName;
    return result;
}

Name &Name::operator=(const Name &name) {
    firstName = name.firstName;
    lastName = name.lastName;
    return *this;
}

bool Name::operator==(const Name &name) {
    return name.firstName == firstName && name.lastName == lastName;
}

bool Name::operator!=(const Name &name) {
    return name.firstName != firstName || name.lastName != lastName;
}

bool Name::operator<(const Name &name) {
    return name.lastName < lastName;
}

bool Name::operator<=(const Name &name) {
    return name.lastName <= lastName;
}

bool Name::operator>(const Name &name) {
    return name.lastName > lastName;
}

bool Name::operator>=(const Name &name) {
    return name.lastName >= lastName;
}
