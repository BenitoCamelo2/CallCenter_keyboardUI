#include <iostream>
#include "../include/util.h"

using namespace std;

int countDigits(int n){
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}

void printSpaces(int n){
    for(int i = 0; i < n; i++){
        printw(" ");
    }
}

//if there is no upper or lower limit, you assign max or min to -1 depending on the situation
bool verifyINT(int min, int max, int n){
    if(max == -1){
        if(n >= min){
            return true;
        } else {
            return false;
        }
    } else if (min == -1){
        if(n <= max){
            return true;
        } else {
            return false;
        }
    } else {
        if(n >= min && n <= max){
            return true;
        } else {
            return false;
        }
    }
}

void agentListHeader(){
    printw("|Nombre             |Codigo             |Especialidad       |Horas        |Horas extras       |");
}

void clientListHeader(){
    printw("|Numero Telefonico  |Fecha de llamada   |Hora inicio de llamada|Duracion de llamada|");
}

string inputString(){
    string result;
    char tempCharacter = getch();
    string tempCharacterStr;

    int x, y;
    int tempX, tempY;
    getyx(stdscr, y, x);
    tempX = x;
    tempY = y;

    while(tempCharacter != ENTER){
        tempCharacterStr = tempCharacter;
        if(int(tempCharacter) == BACKSPACE){
            result.pop_back();
            move(y, x);
            clrtobot();
            printw("%s", result.data());
            tempX = x + result.length();
        } else {
            result += tempCharacter;
            move(tempY, tempX);
            printw("%s", tempCharacterStr.data());
            tempX++;
        }
        tempCharacter = getch();
    }
    return result;
}

int inputInteger(){
    int result;

    int x, y;
    int tempX, tempY;
    getyx(stdscr, y, x);
    tempX = x;
    tempY = y;

    string tempResult;
    char tempCharacter = getch();
    string tempCharacterStr;


    while(tempCharacter != ENTER){
        tempCharacterStr = tempCharacter;
        if(isdigit(tempCharacter)) {
            tempResult += tempCharacter;
            move(tempY, tempX);
            printw("%s", tempCharacterStr.data());
            tempX++;
        } else if(tempCharacter == BACKSPACE){
            tempResult.pop_back();
            move(y, x);
            clrtobot();
            printw("%s", tempResult.data());
            tempX = x + tempResult.length();
        }
        tempCharacter = getch();
    }
    result = atoi(tempResult.data());
    return result;
}