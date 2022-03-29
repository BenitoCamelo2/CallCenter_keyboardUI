#include "../include/AgentMenu.h"
#include "../include/ClientMenu.h"
#include "../include/util.h"

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

AgentMenu::AgentMenu(AgentList* agentList): agentListRef(agentList) {
    mainAgentMenu();
}


void AgentMenu::enterToContinue() {
    int HEIGHT, LENGTH;

    getyx(stdscr, HEIGHT, LENGTH);

    move(HEIGHT, LENGTH);
    printw("Presione enter para continuar...\n");
    getch();
}

void AgentMenu::addAgent() {
    //temp variables to add to the agent variable, then to add to the list
    Agent tempAgent;
    string codeSTR, firstName, lastName;
    Name name;
    Time startTime, endTime;
    int extension, extraHours, specialty, tempHour, tempMinute, codeINT;
    string option;

    //HEIGHT is y axis and LENGTH is x axis
    int HEIGHT, LENGTH;
    HEIGHT = 2;
    LENGTH = 0;

    printw("AGREGAR AGENTE");
    refresh();
    //shows cursor
    curs_set(1);

    //move the cursor to line 2
    move(HEIGHT, LENGTH);
    //code, verify as int then assign to str
    printw("Codigo: ");
    codeSTR = inputString();
    codeINT = atoi(codeSTR.data());
    //if statement activated when code is not valid
    if(!verifyINT(1, -1, codeINT)) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (!verifyINT(1, -1, codeINT)) {
            printw("Ingresa un numero mayor a 0: ");
            codeSTR = inputString();
            codeINT = atoi(codeSTR.data());
        }
    }
    HEIGHT++;

    //first name
    move(HEIGHT, LENGTH);
    printw("Primer nombre: ");
    firstName = inputString();
    //if statement activated if name is empty
    if(firstName.empty()) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (firstName.empty()) {
            printw("Ingresa de nuevo: ");
            LENGTH = 18;
            firstName = inputString();
        }
    }
    HEIGHT++;

    //last name
    move(HEIGHT, LENGTH);
    printw("Apellido: ");
    lastName = inputString();
    //if statement is activated if lastName is empty
    if(lastName.empty()) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (lastName.empty()) {
            printw("Ingresa de nuevo: ");
            lastName = inputString();
        }
    }
    name.setData(firstName, lastName);
    HEIGHT++;


    //Time of when shift starts
    move(HEIGHT, LENGTH);
    printw("Inicio de jornada: ");
    //this is to print where it separates hours and minutes
    printCharacter(':', 2);
    //this moves the cursor to where hour starts
    move(HEIGHT, LENGTH+19);
    tempHour = inputIntegerDigitLimit(2);
    //moves cursor to a position to print : again
    move(HEIGHT, LENGTH+19);
    printCharacter(':', 2);
    //this moves the cursor to where minute starts
    move(HEIGHT, LENGTH+22);
    tempMinute = inputIntegerDigitLimit(2);
    while (!startTime.setData(tempHour, tempMinute)) {
        move(HEIGHT, LENGTH);
        clrtobot();
        refresh();
        printw("Ingresa de nuevo: ");
        printCharacter(':', 2);
        move(HEIGHT+1, LENGTH+18);
        move(HEIGHT, LENGTH+18);
        tempHour = inputIntegerDigitLimit(2);
        move(HEIGHT, LENGTH+21);
        tempMinute = inputIntegerDigitLimit(2);
    }

    HEIGHT++;

    //Time of when shift ends
    move(HEIGHT, LENGTH);
    printw("Fin de jornada: ");
    //this is to print where it separates hours and minutes
    printCharacter(':', 2);
    //this moves the cursor to where hour starts
    move(HEIGHT, LENGTH+16);
    tempHour = inputIntegerDigitLimit(2);
    //moves cursor to a position to print : again
    move(HEIGHT, LENGTH+16);
    printCharacter(':', 2);
    //this moves the cursor to where minute starts
    move(HEIGHT, LENGTH+19);
    tempMinute = inputIntegerDigitLimit(2);
    while (!endTime.setData(tempHour, tempMinute)) {
        move(HEIGHT, LENGTH);
        clrtobot();
        refresh();
        printw("Ingresa de nuevo: ");
        printCharacter(':', 2);
        move(HEIGHT+1, LENGTH+18);
        move(HEIGHT, LENGTH+18);
        tempHour = inputIntegerDigitLimit(2);
        move(HEIGHT, LENGTH+21);
        tempMinute = inputIntegerDigitLimit(2);
    }

    HEIGHT++;

    //extension
    move(HEIGHT, LENGTH);
    printw("Extension: ");
    extension = inputInteger();
    //if statement activated is extension is less than 1
    if(!verifyINT(1, -1, extension)) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (!verifyINT(1, 6, extension)) {
            printw("Ingresa de nuevo mayor o igual a 1: ");
            extension = inputInteger();
        }
    }
    HEIGHT++;

    //extra hours
    move(HEIGHT, LENGTH);
    printw("Horas extras: ");
    extraHours = inputInteger();
    //if statement activated when extraHours is less than 0
    if(!verifyINT(0, -1, extraHours)) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (!verifyINT(0, -1, extraHours)) {
            printw("Ingresa de nuevo mayor o igual a 0: ");
            extraHours = inputInteger();
        }
    }
    HEIGHT++;

    //specialty
    move(HEIGHT, LENGTH);
    printw("Especialidad (1, 2, 3, 4, 5, 6): ");
    specialty = inputInteger();
    HEIGHT++;
    //if statement is activated when specialty is not 1<->6
    if(!verifyINT(1, 6, specialty)) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (!verifyINT(1, 6, specialty)) {
            printw("Ingresa un valor de 1 a 6: ");
            specialty = inputInteger();
        }
    }
    HEIGHT++;

    move(HEIGHT, LENGTH);
    printw("Guste agregar clientes al agente? (s/n): ");
    option = inputString();

    curs_set(0);
    clear();
    refresh();

    if(option == "s" || option == "S"){
        new ClientMenu(tempAgent.getClientList());
    }

    tempAgent.setData(codeSTR, name, startTime, endTime, extension, extraHours, specialty);
    agentListRef->insertData(agentListRef->getFirstPos(), tempAgent);

}

void AgentMenu::deleteAgent() {
    //agent variable to save to search for its position and then delete using that position
    Agent tempAgent;
    AgentNode* agentNode;
    //only searches by code
    string code;
    bool terminate = false;

    erase();
    printw("ELIMINAR AGENTE\n");
    printAgents("");
    printw("Ingresa el codigo del agente que desea eliminar: ");
    cin.ignore();getline(cin, code);
    //while loop to make sure the code entered is valid
    do {
        tempAgent.setCode(code);
        agentNode = agentListRef->findData(tempAgent, SEARCH_CODE);
        if (agentNode == nullptr) {
            printw("Ingresa de nuevo porfavor (0 para cancelar): ");
            getline(cin, code);
            if(code == "0"){
                return;
            }
        } else {
            terminate = true;
        }
    }while(!terminate);
    //deletes the node
    agentListRef->deleteData(agentNode);
}

void AgentMenu::modifyAgent() {
    //same theory as deleteAgent()
    bool terminate = false;
    AgentNode* temp;
    string agentCodeStr;
    int agentCodeInt;
    Agent tempAgent;

    //menu options
    string menuOptions[AGENT_MODIFY_OPTIONS] = {
            "   Codigo                      ",
            "   Nombre                      ",
            "   Hora de inicio de jornada   ",
            "   Hora de fin de jornada      ",
            "   Extension                   ",
            "   Horas extras                ",
            "   Especialidad                ",
            "   Clients                     ",
            "   Regresar                    "};
    int HEIGHT = 10, LENGTH = 50;
    int key = '\0';
    int option = 0;

    curs_set(1);
    refresh();

    printw("MODIFICAR AGENTE\n");
    printAgents("");
    printw("\n");
    //chose agent to modify
    printw("Ingresa el codigo: ");
    agentCodeInt = inputInteger();

    if(!verifyINT(0, -1, agentCodeInt)){
        HEIGHT += 2;
        move(HEIGHT, LENGTH);
        while(!verifyINT(0, -1, agentCodeInt)){
            printw("Ingresa de nuevo: ");
            agentCodeInt = inputInteger();
        }
    }
    HEIGHT++;

    agentCodeStr = to_string(agentCodeInt);
    tempAgent.setCode(agentCodeStr);
    //makes sure the code entered is valid
    curs_set(0);
    refresh();
    while(!terminate){
        temp = agentListRef->findData(tempAgent, SEARCH_CODE);
        if(temp == nullptr){
            curs_set(1);
            refresh();
            printw("Ingresa de nuevo: ");
            agentCodeInt = inputInteger();
            if(!verifyINT(0, -1, agentCodeInt)){
                HEIGHT++;
                move(HEIGHT, LENGTH);
                while(!verifyINT(0, -1, agentCodeInt)){
                    printw("Ingresa de nuevo: ");
                    agentCodeInt = inputInteger();
                    curs_set(0);
                    refresh();
                }
            }
            HEIGHT++;
            agentCodeStr = to_string(agentCodeInt);
            tempAgent.setCode(agentCodeStr);
        } else {
            terminate = true;
        }
    }

    tempAgent = agentListRef->retrieve(temp);

    terminate = false;
    //while loop to modify any attribute
    move(HEIGHT, LENGTH);
    clear();
    refresh();
    do{
        move(5, 55);
        printw("MODIFICANDO %s", tempAgent.getName().getFirstName().data());
        HEIGHT = 10;
        LENGTH = 50;
        move(HEIGHT, LENGTH);
        for(int i = 0; i < AGENT_MODIFY_OPTIONS; i++){
            //selected option is found
            if(i == option){
                if(!has_colors()){
                    printw("Error, terminal no tiene soporte para colores");
                } else {
                    attron(COLOR_PAIR(WHITE_TEXT_BLUE_BACKGROUND));
                    printw("%s", menuOptions[i].data());
                    attroff(COLOR_PAIR(WHITE_TEXT_BLUE_BACKGROUND));
                }
                //selected option is not current option
            } else {
                printw("%s", menuOptions[i].data());
            }
            //go one line down
            HEIGHT += 1;
            move(HEIGHT, LENGTH);
        }
        key = getch();
        switch(key) {
            //option goes up
            case KEY_UP: {
                option--;
                //makes sure option doesn't go farther than options available
                if (option > AGENT_MODIFY_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_MODIFY_OPTIONS;
                }
                break;
            }
                //option goes down
            case KEY_DOWN: {
                option++;
                if (option > AGENT_MODIFY_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_MODIFY_OPTIONS;
                }
                break;
            }
                //user selects desired option
            case ENTER: {
                //makes sure option is valid, just in case
                if (option > AGENT_MODIFY_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_MODIFY_OPTIONS;
                }
                switch (option) {
                    case MODIFY_CODE: {
                        int codeINT;
                        string codeSTR;

                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        curs_set(1);
                        refresh();
                        printw("Ingresa el codigo nuevo: ");
                        codeINT = inputInteger();
                        if(!verifyINT(1, -1, codeINT)) {
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while (!verifyINT(1, -1, codeINT)) {
                                printw("Ingresa de nuevo: ");
                                codeINT = inputInteger();
                            }
                        }
                        curs_set(0);
                        clrtobot();
                        refresh();
                        codeSTR = to_string(codeINT);
                        tempAgent.setCode(codeSTR);
                        break;
                    }
                    case MODIFY_NAME: {
                        string firstName, lastName;
                        Name name;

                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        curs_set(1);
                        refresh();
                        printw("Ingresa el primero nombre: ");
                        firstName = inputString();
                        if(firstName.empty()){
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while(firstName.empty()){
                                printw("Ingresa de nuevo: ");
                                firstName = inputString();
                            }
                        }
                        HEIGHT++;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa su apellido: ");
                        lastName = inputString();
                        if(lastName.empty()){
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while(lastName.empty()){
                                printw("Ingresa de nuevo: ");
                                lastName = inputString();
                            }
                        }
                        name.setData(firstName, lastName);
                        curs_set(0);
                        clrtobot();
                        refresh();
                        tempAgent.setName(name);
                        break;
                    }
                    case MODIFY_START_TIME: {
                        int hour, minute;
                        Time startTime;

                        curs_set(1);
                        refresh();
                        printw("Ingresa la hora: ");
                        hour = inputInteger();
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("Ingresa el minuto: ");
                        minute = inputInteger();

                        if(!startTime.setData(hour, minute)) {
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while (!startTime.setData(hour, minute)) {
                                printw("Ingresa la hora de nuevo: ");
                                hour = inputInteger();
                                printw("Ingresa el minuto de nuevo: ");
                                minute = inputInteger();
                            }
                        }

                        curs_set(0);
                        clrtobot();
                        refresh();
                        tempAgent.setStartTime(startTime);
                        break;
                    }
                    case MODIFY_END_TIME: {
                        int hour, minute;
                        Time endTime;

                        curs_set(1);
                        refresh();
                        printw("Ingresa la hora: ");
                        hour = inputInteger();
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("Ingresa el minuto: ");
                        minute = inputInteger();

                        if(!endTime.setData(hour, minute)) {
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while (!endTime.setData(hour, minute)) {
                                printw("Ingresa la hora de nuevo: ");
                                hour = inputInteger();
                                printw("Ingresa el minuto de nuevo: ");
                                minute = inputInteger();
                            }
                        }

                        curs_set(0);
                        clrtobot();
                        refresh();
                        tempAgent.setEndTime(endTime);
                        break;
                    }
                    case MODIFY_EXTENSION: {
                        int extension;

                        curs_set(1);
                        refresh();
                        printw("Ingresa la extension: ");
                        extension = inputInteger();
                        if(!verifyINT(1, -1, extension)) {
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while (!verifyINT(1, -1, extension)) {
                                printw("Ingresa de nuevo: ");
                                extension = inputInteger();
                            }
                        }

                        curs_set(0);
                        clrtobot();
                        refresh();
                        tempAgent.setExtension(extension);
                        break;
                    }
                    case MODIFY_EXTRA_HOURS: {
                        int extraHours;

                        curs_set(1);
                        refresh();
                        printw("Ingresa las horas extras a sumar: ");
                        extraHours = inputInteger();
                        if(!verifyINT(0, -1, extraHours)) {
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while (!verifyINT(0, -1, extraHours)) {
                                printw("Ingresa de nuevo: ");
                                extraHours = inputInteger();
                            }
                        }

                        curs_set(0);
                        clrtobot();
                        refresh();
                        tempAgent.addExtraHours(extraHours);
                        break;
                    }
                    case MODIFY_SPECIALTY: {
                        int specialty;

                        curs_set(1);
                        refresh();
                        printw("Ingresa la especialidad: ");
                        specialty = inputInteger();
                        if(!verifyINT(1, 6, specialty)) {
                            HEIGHT++;
                            move(HEIGHT, LENGTH);
                            while (!verifyINT(1, 6, specialty)) {
                                printw("Ingresa de nuevo: ");
                                specialty = inputInteger();
                            }
                        }

                        curs_set(0);
                        clrtobot();
                        refresh();
                        tempAgent.setSpecialty(specialty);
                        break;
                    }
                    case MODIFY_CLIENTS: {
                        new ClientMenu(tempAgent.getClientList());
                        break;
                    }
                    case EXIT_MODIFY: {
                        temp->setData(tempAgent);
                        terminate = true;
                        clrtobot();
                        refresh();
                        break;
                    }
                    default: {
                        HEIGHT++;
                        printw("Opcion invalida");
                        HEIGHT++;
                        enterToContinue();
                    }
                }
            }
        }
    }while(!terminate);
}

void AgentMenu::searchAgent() {
    bool terminate = false;

    string searchOptions[AGENT_SEARCH_OPTIONS] = {"   Codigo                      ",
                                                  "   Apellido                    ",
                                                  "   Hora de inicio de jornada   ",
                                                  "   Hora fin de jornada         ",
                                                  "   Extension                   ",
                                                  "   Especialidad                ",
                                                  "   Regresar                    "};

    int HEIGHT, LENGTH;
    int key = '\0';
    int option = 0;

    curs_set(0);
    refresh();

    //chose what to search by
    do{
        HEIGHT = 10, LENGTH = 50;
        move(HEIGHT, LENGTH);
        printw("BUSCAR AGENTE");
        HEIGHT++;
        move(HEIGHT, LENGTH);
        for(int i = 0; i < AGENT_SEARCH_OPTIONS; i++){
            //selected option is found
            if(i == option){
                if(!has_colors()){
                    printw("Error, terminal no tiene soporte para colores");
                } else {
                    attron(COLOR_PAIR(WHITE_TEXT_BLUE_BACKGROUND));
                    printw("%s", searchOptions[i].data());
                    attroff(COLOR_PAIR(WHITE_TEXT_BLUE_BACKGROUND));
                }
                //selected option is not current option
            } else {
                printw("%s", searchOptions[i].data());
            }
            //go one line down
            HEIGHT += 1;
            move(HEIGHT, LENGTH);
        }
        key = getch();
        switch(key){
            //option goes up
            case KEY_UP: {
                option--;
                //makes sure option doesn't go farther than options available
                if (option > AGENT_SEARCH_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_SEARCH_OPTIONS;
                }
                break;
            }
                //option goes down
            case KEY_DOWN: {
                option++;
                if (option > AGENT_SEARCH_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_SEARCH_OPTIONS;
                }
                break;
            }
                //user selects desired option
            case ENTER: {
                //makes sure option is valid, just in case
                if (option > AGENT_SEARCH_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_SEARCH_OPTIONS;
                }
                clear();
                refresh();
                curs_set(1);
                switch(option){
                    //search options
                    case SEARCH_CODE: {
                        string codeStr, cStr;
                        char c;
                        int tempX, tempY;
                        HEIGHT = 2;
                        LENGTH = 50;
                        tempX = HEIGHT;
                        tempY = LENGTH;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa el codigo: ");
                        c = getch();
                        while(c != ENTER){
                            cStr = c;
                            if(int(c) == BACKSPACE){
                                getyx(stdscr, tempY, tempX);
                                if(tempX != LENGTH) {
                                    codeStr.pop_back();
                                    tempX--;
                                    move(tempY, tempX);
                                    printw(" ");
                                    move(tempY, tempX);
                                }
                            } else {
                                codeStr += c;
                                move(tempY, tempX);
                                printw("%s", cStr.data());
                                tempX++;
                            }
                            searchPrintAgents(SEARCH_CODE, codeStr);
                            c = getch();
                        }
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        break;
                    }
                    case SEARCH_LAST_NAME: {
                        string lastName, cStr;
                        char c;
                        int tempX, tempY;
                        HEIGHT = 2;
                        LENGTH = 50;
                        tempX = HEIGHT;
                        tempY = LENGTH;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa el codigo: ");
                        c = getch();
                        while(c != ENTER){
                            cStr = c;
                            if(int(c) == BACKSPACE){
                                getyx(stdscr, tempY, tempX);
                                if(tempX != LENGTH) {
                                    lastName.pop_back();
                                    tempX--;
                                    move(tempY, tempX);
                                    printw(" ");
                                    move(tempY, tempX);
                                }
                            } else {
                                lastName += c;
                                move(tempY, tempX);
                                printw("%s", cStr.data());
                                tempX++;
                            }
                            searchPrintAgents(SEARCH_LAST_NAME, lastName);
                            c = getch();
                        }
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        break;
                    }
                    case SEARCH_HOUR_START: {
                        string hour, cStr;
                        char c;
                        int tempX, tempY;
                        HEIGHT = 2;
                        LENGTH = 50;
                        tempX = HEIGHT;
                        tempY = LENGTH;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa el codigo: ");
                        c = getch();
                        while(c != ENTER){
                            cStr = c;
                            if(int(c) == BACKSPACE){
                                getyx(stdscr, tempY, tempX);
                                if(tempX != LENGTH) {
                                    hour.pop_back();
                                    tempX--;
                                    move(tempY, tempX);
                                    printw(" ");
                                    move(tempY, tempX);
                                }
                            } else {
                                hour += c;
                                move(tempY, tempX);
                                printw("%s", cStr.data());
                                tempX++;
                            }
                            searchPrintAgents(SEARCH_HOUR_START, hour);
                            c = getch();
                        }
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        break;
                    }
                    case SEARCH_HOUR_END: {
                        string hour, cStr;
                        char c;
                        int tempX, tempY;
                        HEIGHT = 2;
                        LENGTH = 50;
                        tempX = HEIGHT;
                        tempY = LENGTH;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa el codigo: ");
                        c = getch();
                        while(c != ENTER){
                            cStr = c;
                            if(int(c) == BACKSPACE){
                                getyx(stdscr, tempY, tempX);
                                if(tempX != LENGTH) {
                                    hour.pop_back();
                                    tempX--;
                                    move(tempY, tempX);
                                    printw(" ");
                                    move(tempY, tempX);
                                }
                            } else {
                                hour += c;
                                move(tempY, tempX);
                                printw("%s", cStr.data());
                                tempX++;
                            }
                            searchPrintAgents(SEARCH_HOUR_END, hour);
                            c = getch();
                        }
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        break;
                    }
                    case SEARCH_EXTENSION: {
                        string extension, cStr;
                        char c;
                        int tempX, tempY;
                        HEIGHT = 2;
                        LENGTH = 50;
                        tempX = HEIGHT;
                        tempY = LENGTH;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa el codigo: ");
                        c = getch();
                        while(c != ENTER){
                            cStr = c;
                            if(int(c) == BACKSPACE){
                                getyx(stdscr, tempY, tempX);
                                if(tempX != LENGTH) {
                                    extension.pop_back();
                                    tempX--;
                                    move(tempY, tempX);
                                    printw(" ");
                                    move(tempY, tempX);
                                }
                            } else {
                                extension += c;
                                move(tempY, tempX);
                                printw("%s", cStr.data());
                                tempX++;
                            }
                            searchPrintAgents(SEARCH_EXTENSION, extension);
                            c = getch();
                        }
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        break;
                    }
                    case SEARCH_SPECIALTY: {
                        string specialty, cStr;
                        char c;
                        int tempX, tempY;
                        HEIGHT = 2;
                        LENGTH = 50;
                        tempX = HEIGHT;
                        tempY = LENGTH;

                        move(HEIGHT, LENGTH);
                        printw("Ingresa el codigo: ");
                        c = getch();
                        while(c != ENTER){
                            cStr = c;
                            if(int(c) == BACKSPACE){
                                getyx(stdscr, tempY, tempX);
                                if(tempX != LENGTH) {
                                    specialty.pop_back();
                                    tempX--;
                                    move(tempY, tempX);
                                    printw(" ");
                                    move(tempY, tempX);
                                }
                            } else {
                                specialty += c;
                                move(tempY, tempX);
                                printw("%s", cStr.data());
                                tempX++;
                            }
                            searchPrintAgents(SEARCH_HOUR_START, specialty);
                            c = getch();
                        }
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        break;
                    }
                    case EXIT_SEARCH: {
                        terminate = true;
                        break;
                    }
                    default: {
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("Seleccione una opcion valida");
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        enterToContinue();
                        clrtobot();
                        refresh();
                    }
                }
                break;
            }
        }
        curs_set(0);
        clear();
        refresh();
    }while(!terminate);
}

void AgentMenu::searchPrintAgents(const int &searchBy, string &searchTerm) {
    AgentNode* temp(agentListRef->getFirstPos());
    AgentNode* last(agentListRef->getLastPos());

    int HEIGHT, LENGTH;
    getyx(stdscr, HEIGHT, LENGTH);
    move(HEIGHT+1, 0);
    clrtobot();
    int tempX = 42, tempY = HEIGHT;

    start_color();

    if(searchTerm.empty()){
        clrtobot();
        refresh();
    } else if(temp != nullptr) {
    //makes sure there is at least 1 agent, or else it breaks
        tempY += 2;
        move(tempY, tempX);
        attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
        printw("|Nombre             |Codigo             |");
        attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
        switch(searchBy){
            case SEARCH_CODE: {
                while (temp != nullptr) {
                    if(temp->getData().getCode().find(searchTerm) != -1) {
                        getyx(stdscr, tempY, tempX);
                        move(tempY, 42);
                        printAgentSumarized(temp);
                    }
                    temp = temp->getNext();
                }
                break;
            }
            case SEARCH_LAST_NAME: {
                while(temp != nullptr){
                    if(temp->getData().getName().getLastName().find(searchTerm) != -1){
                        getyx(stdscr, tempY, tempX);
                        move(tempY, 42);
                        printAgentSumarized(temp);
                    }
                    temp = temp->getNext();
                }
                break;
            }
            case SEARCH_HOUR_START: {
                while(temp != nullptr){
                    if(to_string(temp->getData().getStartTime().getHour()).find(searchTerm) != -1){
                        getyx(stdscr, tempY, tempX);
                        move(tempY, 42);
                        printAgentSumarized(temp);
                    }
                    temp = temp->getNext();
                }
                break;
            }
            case SEARCH_HOUR_END: {
                while(temp != nullptr){
                    if(to_string(temp->getData().getEndTime().getHour()).find(searchTerm) != -1){
                        getyx(stdscr, tempY, tempX);
                        move(tempY, 42);
                        printAgentSumarized(temp);
                    }
                    temp = temp->getNext();
                }
                break;
            }
            case SEARCH_EXTENSION: {
                while(temp != nullptr){
                    if(to_string(temp->getData().getExtension()).find(searchTerm) != -1){
                        getyx(stdscr, tempY, tempX);
                        move(tempY, 42);
                        printAgentSumarized(temp);
                    }
                    temp = temp->getNext();
                }
                break;
            }
            case SEARCH_SPECIALTY: {
                while(temp != nullptr){
                    if(to_string(temp->getData().getSpecialty()).find(searchTerm) != -1){
                        getyx(stdscr, tempY, tempX);
                        move(tempY, 42);
                        printAgentSumarized(temp);
                    }
                    temp = temp->getNext();
                }
                break;
            }
            default: {
                tempY++;
                move(tempY, tempX);
                printw("Error en busqueda");
            }
        }
    } else {
        tempY++;
        move(tempY, LENGTH);
        printw("No hay agentes en la lista");
    }
    move(HEIGHT, LENGTH);
}

void AgentMenu::sortAgents() {

}

void AgentMenu::printAgent(AgentNode* agentNode) {
    string extraHours;

    int x, y;
    getyx(stdscr, y, x);
    move(y+1, x);

    printw("|%s", agentNode->getData().getName().toString().data());
    printSpaces(19 - agentNode->getData().getName().toString().length());
    printw("|%s", agentNode->getData().getCode().data());
    printSpaces(19 - agentNode->getData().getCode().length());
    printw("|");
    switch(agentNode->getData().getSpecialty()){
        case SERVIDORES: {
            printw("Servidores         ");
            break;
        }
        case ESCRITORIO: {
            printw("Escritorio         ");
            break;
        }
        case PORTATILES: {
            printw("Portatiles         ");
            break;
        }
        case LINUX: {
            printw("Linux              ");
            break;
        }
        case IMPRESORAS: {
            printw("Impresoras         ");
            break;
        }
        case REDES: {
            printw("Redes              ");
            break;
        }
        default: {
            printw("ERROR\n");
            break;
        }
    }
    printw("|%s", agentNode->getData().getStartTime().toString().data());
    printw(" - %s", agentNode->getData().getEndTime().toString().data());
    extraHours = to_string(agentNode->getData().getExtraHours());
    printw("|%s", extraHours.data());
    printSpaces(19 - countDigits(agentNode->getData().getExtraHours()));
    printw("|");
}

void AgentMenu::printAgentSumarized(AgentNode* agentNode) {
    int x, y;
    getyx(stdscr, y, x);
    move(y+1, x);
    printw("|%s", agentNode->getData().getName().toString().data());
    printSpaces(19 - agentNode->getData().getName().toString().size());
    printw("|%s", agentNode->getData().getCode().data());
    printSpaces(19 - agentNode->getData().getCode().length());
    printw("|");
}

void AgentMenu::printClient(ClientNode* clientNode){
    int x, y;
    getyx(stdscr, y, x);
    move(y+1, x);

    //prints data in this structure:
    //|PhoneNumber|CallDate|CallStart|CallDuration|
    //can always build it some day to calculate when the call ended
    printw("|%s", clientNode->getData().getPhoneNumber().data());
    printSpaces(19 - clientNode->getData().getPhoneNumber().length());
    printw("|%s", clientNode->getData().getCallDate().toString().data());
    printSpaces(19 - clientNode->getData().getCallDate().toString().length());
    printw("|%s", clientNode->getData().getCallStart().toString().data());
    printSpaces(22 - clientNode->getData().getCallStart().toString().length());
    printw("|%s", clientNode->getData().getCallDuration().toString().data());
    printSpaces(19 - clientNode->getData().getCallDuration().toString().length());
    printw("|");
}

void AgentMenu::printAgents(const string& option) {
    AgentNode* temp(agentListRef->getFirstPos());
    AgentNode* last(agentListRef->getLastPos());

    int HEIGHT, LENGTH;

    getyx(stdscr, HEIGHT, LENGTH);

    move(HEIGHT, LENGTH);

    start_color();

    //makes sure there is at least 1 agent, or else it breaks
    if(temp != nullptr) {
        //prints the first line of the list, which shows the categories
        attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
        printw("-----------------------------------------------------------------------------------------------");
        attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
        HEIGHT++;
        move(HEIGHT, LENGTH);
        agentListHeader();
        //in this case there is only one element in the list
        if(temp == last) {
            if(option == "s" || option == "S"){
                move(HEIGHT, 0);
                printAgent(temp);
                if(temp->getData().getClientList()->getFirstPos() != nullptr) {
                    printw("\t");
                    attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
                    printw("------------------------------------------------------------------------------------");
                    attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
                    HEIGHT++;
                    move(HEIGHT, LENGTH);
                    printw("\t");
                    clientListHeader();
                    HEIGHT++;
                    move(HEIGHT, LENGTH);
                    printClients(temp);
                }
            } else {
                move(HEIGHT, 0);
                printAgent(temp);
            }
        //more than one element in the list
        } else {
            if(option == "s" || option == "S"){
                while (temp != nullptr) {
                    getyx(stdscr, HEIGHT, LENGTH);
                    move(HEIGHT, 0);
                    move(HEIGHT, 0);
                    printAgent(temp);
                    if(temp->getData().getClientList()->getFirstPos() != nullptr) {
                        printw("\t");
                        attron(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
                        printw("------------------------------------------------------------------------------------");
                        attroff(COLOR_PAIR(GREEN_TEXT_DEFAULT_BACKGROUND));
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("\t");
                        clientListHeader();
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printClients(temp);
                    }
                    temp = temp->getNext();
                }

            } else {
                while (temp != nullptr) {
                    getyx(stdscr, HEIGHT, LENGTH);
                    move(HEIGHT, 0);
                    printAgent(temp);
                    temp = temp->getNext();
                }
            }
        }
    } else {
        printw("No hay agentes en la lista");
    }
    getyx(stdscr, HEIGHT, LENGTH);
    HEIGHT++;
    move(HEIGHT, 0);
    enterToContinue();
    clear();
    refresh();
}

void AgentMenu::printClients(AgentNode* agentNode){
    ClientNode* temp(agentNode->getData().getClientList()->getFirstPos());
    ClientNode* last(agentNode->getData().getClientList()->getLastPos());

    int HEIGHT, LENGTH;
    getyx(stdscr, HEIGHT, LENGTH);

    move(HEIGHT, LENGTH);
    //makes sure there are nodes in the list
    if(temp != nullptr) {
        //this is when there is only one client in the list
        if (temp == last) {
            printw("\t");
            printClient(temp);
        //multiple clients in the list
        } else {
            while (temp != nullptr) {
                printw("\t");
                printClient(temp);
                temp = temp->getNext();
            }
        }
    } else {
        printw("No hay clientes en la lista");
    }
    HEIGHT++;
    LENGTH = 0;
}

void AgentMenu::mainAgentMenu() {
    bool terminate = false;
    int option = 0;
    int key = '\0';
    int HEIGHT, LENGTH;
    //array of menu options
    string menuOptions[AGENT_MENU_OPTIONS] = {
            "   Agregar agente               ",
            "   Eliminar agente              ",
            "   Modificar agente             ",
            "   Buscar agente                ",
            "   Organizar agentes            ",
            "   Mostrar los agentes          ",
            "   Eliminar TODOS los agentes   ",
            "   Salir                        "
    };

    //color pair for selecting an option
    start_color();
    init_pair(WHITE_TEXT_BLUE_BACKGROUND, COLOR_WHITE, COLOR_CYAN);
    init_pair(RED_TEXT_DEFAULT_BACKGROUND, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_TEXT_DEFAULT_BACKGROUND, COLOR_GREEN, COLOR_BLACK);

    //clear the screen
    clear();
    refresh();

    //prints the agent menu
    do{
        attron(COLOR_PAIR(RED_TEXT_DEFAULT_BACKGROUND));
        move(5, 35);
        printw("Use las flechas y enter para seleccionar una opcion");
        attroff(COLOR_PAIR(RED_TEXT_DEFAULT_BACKGROUND));
        //HEIGHT = y axis
        HEIGHT = 10;
        //LENGTH = x axis
        LENGTH = 45;
        //moves to "center" of screen
        move(HEIGHT, LENGTH);
        //prints menu options, when selected option is found it prints it with highlight
        for(int i = 0; i < AGENT_MENU_OPTIONS; i++){
            //selected option is found
            if(i == option){
                if(!has_colors()){
                    printw("Error, terminal no tiene soporte para colores");
                } else {
                    attron(COLOR_PAIR(WHITE_TEXT_BLUE_BACKGROUND));
                    printw("%s", menuOptions[i].data());
                    attroff(COLOR_PAIR(WHITE_TEXT_BLUE_BACKGROUND));
                }
            //selected option is not current option
            } else {
                printw("%s", menuOptions[i].data());
            }
            //go one line down
            HEIGHT += 1;
            move(HEIGHT, LENGTH);
        }
        //gets keystroke from user
        key = getch();
        switch(key){
            //option goes up
            case KEY_UP: {
                option--;
                //makes sure option doesn't go farther than options available
                if(option >= AGENT_MENU_OPTIONS){
                    option = 0;
                } else if(option < 0){
                    option = AGENT_MENU_OPTIONS-1;
                }
                break;
            }
            //option goes down
            case KEY_DOWN: {
                option++;
                if(option >= AGENT_MENU_OPTIONS){
                    option = 0;
                } else if(option < 0){
                    option = AGENT_MENU_OPTIONS-1;
                }
                break;
            }
            //user selects desired option
            case ENTER: {
                //makes sure option is valid, just in case
                if(option >= AGENT_MENU_OPTIONS){
                    option = 0;
                } else if(option < 0){
                    option = AGENT_MENU_OPTIONS-1;
                }
                switch(option){
                    //user chooses an option
                    case ADD_AGENT: {
                        clear();
                        refresh();
                        addAgent();
                        break;
                    }
                    case DELETE_AGENT: {
                        clear();
                        refresh();
                        deleteAgent();
                        break;
                    }
                    case MODIFY_AGENT: {
                        clear();
                        refresh();
                        modifyAgent();
                        break;
                    }
                    case SEARCH_AGENT: {
                        clear();
                        refresh();
                        searchAgent();
                        break;
                    }
                    case SORT_AGENTS: {
                        clear();
                        refresh();
                        sortAgents();
                        break;
                    }
                    case SHOW_AGENTS: {
                        string options;
                        printw("Guste ver los clientes tambien? (S/N): ");
                        options = inputString();
                        clear();
                        refresh();
                        move(0, 0);
                        printw("MOSTRAR AGENTES");
                        move(2, 0);
                        printAgents(options);
                        refresh();
                        break;
                    }
                    case DELETE_ALL_AGENTS: {
                        string deleteAgents;
                        printw("Esta seguro? (S/N): ");
                        deleteAgents = inputString();
                        if(deleteAgents == "s" || deleteAgents == "S"){
                            agentListRef->deleteAll();
                            getyx(stdscr, HEIGHT, LENGTH);
                            HEIGHT++;
                            LENGTH = 0;
                            enterToContinue();
                        }
                        clear();
                        refresh();
                        break;
                    }
                    case EXIT_AGENT: {
                        terminate = true;
                        break;
                    }
                    default: {
                        getyx(stdscr, HEIGHT, LENGTH);
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("Opcion invalida");
                        HEIGHT++;
                        enterToContinue();
                        break;
                    }
                }
            }
            default: {
                //if client inputs something else than ENTER, UP or DOWN, it displays this message

                break;
            }
        }

    }while(!terminate);
}