#ifndef PROGRAMA_UTIL_H
#define PROGRAMA_UTIL_H

#include <iostream>
#include <ncurses/ncurses.h>
#include <ctype.h>

using namespace std;

#define WHITETEXT_BLUEBACKGROUND 1
#define REDTEXT_DEFAULTBACKGROUND 2

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 10
#define BACKSPACE 8

enum opcionesSplash{
    SPLASH_AGENTE=1,
    SPLASH_CLIENTE,
    SPLASH_READ,
    SPLASH_WRITE
};

int countDigits(int n);

void printSpaces(int n);

bool verifyINT(int min, int max, int n);

void agentListHeader();

void clientListHeader();

string inputString();
int inputInteger();


#endif //PROGRAMA_UTIL_H
