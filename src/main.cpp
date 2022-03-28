#include <ncurses/ncurses.h>
#include <iostream>
#include "../include/MainMenu.h"

using namespace std;

//void printMainMenu(int option);

int main() {

    initscr();

    //hides the cursor
    curs_set(0);
    //doesn't repeat the character the user inputs
    noecho();
    //enables recording of arrow keys, function keys
    keypad(stdscr, TRUE);
    //doesn't require enter to register key
    raw();

    MainMenu mainMenu = MainMenu();

    endwin();
}

    /*
    //variable to end the loop
    bool terminate;
    //variable to temporarly save char
    int c;
    //variable to save menu option
    int option = 0;

    //starts ncurses
    initscr();
    //prints the main menu
    printMainMenu(option);
    //hides the cursor
    curs_set(0);
    //doesn't repeat the character the user inputs
    noecho();
    //enables recording of arrow keys, function keys
    keypad(stdscr, TRUE);
    //doesn't require enter to register key
    raw();

    do{
        //gets key
        c = getch();
        switch(c){
            case KEY_UP: {
                option--;
                break;
            }
            case KEY_DOWN: {
                option++;
                break;
            }
            case ENTER: {
                erase();
                move(10, 50);
                switch(option){
                    case 0: {
                        printw("Option 1");
                        break;
                    }
                    case 1: {
                        printw("Option 2");
                        break;
                    }
                    case 2: {
                        printw("Option 3");
                        break;
                    }
                    default: {
                        printw("Error");
                        break;
                    }
                }
                getch();
                terminate = true;
                break;
            }
            default: {
                move(MENU_OPTION_COUNT + 10, 35);
                printw("Use the up and down arrows to navigate menu");
                break;
            }
        }
        if(option < 0){
            option = MENU_OPTION_COUNT-1;
        } else if(option >= MENU_OPTION_COUNT){
            option = 0;
        }
        printMainMenu(option);
    }while(!terminate);

    //ends ncurses
    endwin();

}

void printMainMenu(int option){
    int y = 10, x = 50;
    string options[MENU_OPTION_COUNT] = {" Option 1 ",
                         " Option 2 ",
                         " Option 3 "};
    string tempLine;

    raw();

    //starts colors
    start_color();

    //creates color pair
    init_pair(1, COLOR_WHITE, COLOR_CYAN);

    //moves cursor to "center" of terminal
    move(y, x);

    //prints main menu
    for(int i = 0; i < MENU_OPTION_COUNT; i++){
        tempLine = options[i];
        //if the menu option is equal to i, it colors the option in cyan
        if(i == option){
            if(!has_colors()){
                printw("Terminal does not support colors");
            }
            //prints colored option
            attron(COLOR_PAIR(1));
            printw("%s", tempLine.data());
            attroff(COLOR_PAIR(1));
        } else {
            //prints the option without color
            printw("%s", tempLine.data());
        }
        //go one line down
        y += 1;
        move(y, x);
    }
}*/