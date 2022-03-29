#ifndef PROGRAMA_UTIL_H
#define PROGRAMA_UTIL_H

#include <iostream>
#include <ncurses/ncurses.h>
#include <ctype.h>

using namespace std;

#define WHITE_TEXT_BLUE_BACKGROUND 1
#define RED_TEXT_DEFAULT_BACKGROUND 2
#define GREEN_TEXT_DEFAULT_BACKGROUND 3

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

void printCharacter(char character, int distanceX);

bool verifyINT(int min, int max, int n);

void agentListHeader();

void clientListHeader();

string inputString();
string inputStringCharacterLimit(int limit);
int inputInteger();
int inputIntegerDigitLimit(int digits);



#endif //PROGRAMA_UTIL_H
