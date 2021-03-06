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

//simple code to print a character at a desired x distance, maybe y will be added
void printCharacter(char character, int distanceX){
    int HEIGHT, LENGTH;

    //gets origen of cursor position
    getyx(stdscr, HEIGHT, LENGTH);

    //moves desired distance from origen
    move(HEIGHT, LENGTH+distanceX);
    //prints character
    printw("%c", character);
    //moves back to origin
    move(HEIGHT, LENGTH);
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

//agent list header
void agentListHeader(){
    start_color();
    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
    printw("|Nombre             |Codigo             |Especialidad       |Horas        |Horas extras       |");
    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
}

//client list header
void clientListHeader(){
    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
    printw("|Numero Telefonico  |Fecha de llamada   |Hora inicio de llamada|Duracion de llamada|");
    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
}

//function to get string input
string inputString(){
    //result is returned as the input string
    string result;
    //temporarly gets input
    char tempCharacter = getch();
    //converts the input to string
    string tempCharacterStr;

    //position data, x and y keep original position
    //should use to verify someone doesn't backspace too far (-1)
    int x, y;
    int tempX, tempY;
    getyx(stdscr, y, x);
    tempX = x;
    tempY = y;

    //starts color attribute, might make parameter
    start_color();
    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));

    //gets input
    while(tempCharacter != ENTER){
        tempCharacterStr = tempCharacter;
        if(int(tempCharacter) == BACKSPACE){
            getyx(stdscr, tempY, tempX);
            if(tempX != x) {
                result.pop_back();
                tempX--;
                move(tempY, tempX);
                printw(" ");
                move(tempY, tempX);
            }
        } else {
            result += tempCharacter;
            move(tempY, tempX);
            printw("%s", tempCharacterStr.data());
            tempX++;
        }
        tempCharacter = getch();
    }

    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));

    //sends string back
    return result;
}

string inputStringCharacterLimit(int limit){
    //result is returned as the input string
    string result;
    //temporarly gets input
    char tempCharacter = getch();
    //converts the input to string
    string tempCharacterStr;
    bool characterLimit = false;

    //position data, x and y keep original position
    //should use to verify someone doesn't backspace too far (-1)
    int x, y;
    int tempX, tempY;
    getyx(stdscr, y, x);
    tempX = x;
    tempY = y;

    //starts color attribute, might make parameter
    start_color();
    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));

    //gets input
    while(tempCharacter != ENTER) {
        if (characterLimit) {
            move(tempY + 1, 0);
            clrtobot();
            move(tempY, tempX);
            refresh();
        }
        tempCharacterStr = tempCharacter;
        if (result.length() < limit && tempCharacter != BACKSPACE) {
            result += tempCharacter;
            move(tempY, tempX);
            printw("%s", tempCharacterStr.data());
            tempX++;
        } else if (tempCharacter != BACKSPACE) {
            move(tempY + 1, tempX);
            printw("Limite de %d digitos, presione Intro para continuar", limit);
            move(tempY, tempX);
            characterLimit = true;
        }
        if (int(tempCharacter) == BACKSPACE) {
            getyx(stdscr, tempY, tempX);
            if (tempX != x) {
                result.pop_back();
                tempX--;
                move(tempY, tempX);
                printw(" ");
                move(tempY, tempX);
            }
            tempCharacter = getch();
        }
    }

    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));

    //sends string back
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

    start_color();
    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));

    while(tempCharacter != ENTER){
        tempCharacterStr = tempCharacter;
        if(isdigit(tempCharacter)) {
            tempResult += tempCharacter;
            move(tempY, tempX);
            printw("%s", tempCharacterStr.data());
            tempX++;
        } else if(tempCharacter == BACKSPACE){
            getyx(stdscr, tempY, tempX);
            if(tempX != x) {
                tempResult.pop_back();
                tempX--;
                move(tempY, tempX);
                printw(" ");
                move(tempY, tempX);
            }
        }
        tempCharacter = getch();
    }
    result = atoi(tempResult.data());

    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));

    return result;
}

int inputIntegerDigitLimit(int digits){
    int result;

    int x, y;
    int tempX, tempY;
    getyx(stdscr, y, x);
    tempX = x;
    tempY = y;

    string tempResult;
    char tempCharacter = getch();
    string tempCharacterStr;
    bool digitLimit = false;

    start_color();
    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));


    while(tempCharacter != ENTER && tempCharacter != ' '){
        if(digitLimit){
            move(tempY+1, 0);
            clrtobot();
            move(tempY, tempX);
            refresh();
        }
        tempCharacterStr = tempCharacter;
        if(tempResult.length() < digits){
            if(isdigit(tempCharacter)) {
                tempResult += tempCharacter;
                move(tempY, tempX);
                printw("%s", tempCharacterStr.data());
                tempX++;
            }
        } else if(tempCharacter != BACKSPACE) {
            move(tempY+1, tempX);
            printw("Limite de %d digitos, presione Intro para continuar", digits);
            move(tempY, tempX);
            digitLimit = true;
        }
        if(tempCharacter == BACKSPACE){
            getyx(stdscr, tempY, tempX);
            if(tempX != x) {
                tempResult.pop_back();
                tempX--;
                move(tempY, tempX);
                printw(" ");
                move(tempY, tempX);
            }
        }
        tempCharacter = getch();

    }
    if(digitLimit){
        move(tempY+1, 0);
        clrtobot();
        move(tempY, tempX);
        refresh();
    }
    result = atoi(tempResult.data());
    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
    return result;
}