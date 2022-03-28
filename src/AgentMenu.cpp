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

    //hour of when shift starts
    move(HEIGHT, LENGTH);
    printw("Hora de inicio de horario: ");
    tempHour = inputInteger();
    HEIGHT++;

    //minute of when shift starts
    move(HEIGHT, LENGTH);
    printw("Minuto de inicio de horario: ");
    tempMinute = inputInteger();
    HEIGHT++;
    //if statement activated if the hour or minute is not valid
    if(!startTime.setData(tempHour, tempMinute)) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (!startTime.setData(tempHour, tempMinute)) {
            int TEMP_HEIGHT = HEIGHT;
            printw("Ingresa la hora de nuevo: ");
            tempHour = inputInteger();
            TEMP_HEIGHT++;
            move(TEMP_HEIGHT, LENGTH);
            printw("Ingresa el minuto de nuevo: ");
            tempMinute = inputInteger();
        }
        HEIGHT += 2;
    }

    //hour of when shift ends
    move(HEIGHT, LENGTH);
    printw("Hora de fin de horario: ");
    tempHour = inputInteger();
    HEIGHT++;
    move(HEIGHT, LENGTH);
    //minute of when shift ends
    printw("Minuto de fin de horario: ");
    tempMinute = inputInteger();
    HEIGHT++;
    //if statement activated when hour or minute is not valid
    if(!endTime.setData(tempHour, tempMinute)) {
        HEIGHT++;
        move(HEIGHT, LENGTH);
        while (!endTime.setData(tempHour, tempMinute)) {
            int TEMP_HEIGHT = HEIGHT;
            printw("Ingresa la hora de nuevo: ");
            tempHour = inputInteger();
            TEMP_HEIGHT++;
            move(TEMP_HEIGHT, LENGTH);
            printw("Ingresa el minuto de nuevo: ");
            tempMinute = inputInteger();
        }
        HEIGHT += 2;
    }

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
                    attron(COLOR_PAIR(WHITETEXT_BLUEBACKGROUND));
                    printw("%s", menuOptions[i].data());
                    attroff(COLOR_PAIR(WHITETEXT_BLUEBACKGROUND));
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
                if (option > AGENT_MENU_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_MENU_OPTIONS;
                }
                break;
            }
                //option goes down
            case KEY_DOWN: {
                option++;
                if (option > AGENT_MENU_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_MENU_OPTIONS;
                }
                break;
            }
                //user selects desired option
            case ENTER: {
                //makes sure option is valid, just in case
                if (option > AGENT_MENU_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = AGENT_MENU_OPTIONS;
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
                        printw("Opcion invalida");
                        enterToContinue();
                    }
                }
            }
        }
    }while(!terminate);
}

void AgentMenu::searchAgent() {
    bool terminate = false;

    //chose what to search by
    do{
        int option = 0;
        erase();
        printw("BUSCAR AGENTE\n");
        printw("Buscar por: ");
        printw("1. Codigo");
        printw("2. Apellido");
        printw("3. Hora de inicio de horario");
        printw("4. Hora de fin de horario");
        printw("5. Extension");
        printw("6. Especialidad");
        printw("7. Regresar");
        printw("Opcion: ");
        cin >> option;
        switch(option){
        //search options
            case SEARCH_CODE: {
                int codeINT;
                string codeSTR;
                Agent tempAgent;

                printw("Ingresa un codigo: ");
                cin >> codeINT;
                while(!verifyINT(1,-1,codeINT)){
                    printw("Ingresa de nuevo: ");
                    cin >> codeINT;
                }
                codeSTR = to_string(codeINT);
                tempAgent.setCode(codeSTR);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_CODE));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_LAST_NAME: {
                string lastName, firstName;
                Name name;
                Agent tempAgent;

                printw("Ingresa el apellido: ");
                cin.ignore();getline(cin, lastName);
                name.setData(firstName, lastName);
                tempAgent.setName(name);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_LAST_NAME));
                enterToContinue();
                break;
            }
            case SEARCH_HOUR_START: {
                int hour, minute=0;
                Time time;
                Agent tempAgent;

                printw("Ingresa la hora de inicio: ");
                cin >> hour;

                while(!time.setData(hour, minute)){
                    printw("Ingresa la hora de nuevo: ");
                    cin >> hour;
                }
                tempAgent.setStartTime(time);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_HOUR_START));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_HOUR_END: {
                int hour, minute=0;
                Time time;
                Agent tempAgent;

                printw("Ingresa la hora de fin: ");
                cin >> hour;

                while(!time.setData(hour, minute)){
                    printw("Ingresa la hora de nuevo: ");
                    cin >> hour;
                }
                tempAgent.setEndTime(time);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_HOUR_END));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_EXTENSION: {
                int extension;
                Agent tempAgent;

                printw("Ingresa la extension: ");
                cin >> extension;
                while(!verifyINT(0, -1, extension)){
                    printw("Ingresa de nuevo: ");
                    cin >> extension;
                }
                tempAgent.setExtension(extension);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_EXTENSION));
                cin.ignore();enterToContinue();
                break;
            }
            case SEARCH_SPECIALTY: {
                int specialty;
                Agent tempAgent;

                printw("Ingresa la especialidad: ");
                cin >> specialty;
                while(!verifyINT(1, 6, specialty)){
                    printw("Ingresa de nuevo: ");
                    cin >> specialty;
                }

                tempAgent.setSpecialty(specialty);

                agentListHeader();
                printAgent(agentListRef->findData(tempAgent, SEARCH_SPECIALTY));
                cin.ignore();enterToContinue();
                break;
            }
            case EXIT_SEARCH: {
                terminate = true;
                break;
            }
            default: {
                printw("Seleccione una opcion valida");
                cin.ignore();
                enterToContinue();
            }
        }
    }while(!terminate);
}

void AgentMenu::sortAgents() {

}

void AgentMenu::printAgent(AgentNode* agentNode) {
    string extraHours;

    printw("|%s", agentNode->getData().getName().toString().data());
    printSpaces(19 - agentNode->getData().getName().toString().size());
    printw("|%s", agentNode->getData().getCode().data());
    printSpaces(19 - agentNode->getData().getCode().size());
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

void AgentMenu::printClient(ClientNode* clientNode){
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

    //makes sure there is at least 1 agent, or else it breaks
    if(temp != nullptr) {
        //prints the first line of the list, which shows the categories
        printw("-----------------------------------------------------------------------------------------------");
        HEIGHT++;
        move(HEIGHT, LENGTH);
        agentListHeader();
        HEIGHT++;
        move(HEIGHT, LENGTH);
        //in this case there is only one element in the list
        if(temp == last) {
            if(option == "s" || option == "S"){
                printAgent(temp);
                if(temp->getData().getClientList()->getFirstPos() != nullptr) {
                    HEIGHT++;
                    move(HEIGHT, LENGTH);
                    printw("\t");
                    printw("------------------------------------------------------------------------------------");
                    HEIGHT++;
                    move(HEIGHT, LENGTH);
                    printw("\t");
                    clientListHeader();
                    HEIGHT++;
                    move(HEIGHT, LENGTH);
                    printClients(temp);
                    HEIGHT++;
                    move(HEIGHT, LENGTH);
                }
            } else {
                printAgent(temp);
            }
        //more than one element in the list
        } else {
            if(option == "s" || option == "S"){
                while (temp != nullptr) {
                    agentListHeader();
                    printAgent(temp);
                    if(temp->getData().getClientList()->getFirstPos() != nullptr) {
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("\t");
                        printw("------------------------------------------------------------------------------------");
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printw("\t");
                        clientListHeader();
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                        printClients(temp);
                        HEIGHT++;
                        move(HEIGHT, LENGTH);
                    }
                    temp = temp->getNext();
                }

            } else {
                while (temp != nullptr) {
                    printAgent(temp);
                    temp = temp->getNext();
                }
            }
        }
    } else {
        printw("No hay agentes en la lista");
    }
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
    init_pair(WHITETEXT_BLUEBACKGROUND, COLOR_WHITE, COLOR_CYAN);
    init_pair(REDTEXT_DEFAULTBACKGROUND, COLOR_RED, COLOR_BLACK);

    //clear the screen
    clear();
    refresh();

    //prints the agent menu
    do{
        attron(COLOR_PAIR(REDTEXT_DEFAULTBACKGROUND));
        move(5, 35);
        printw("Use las flechas y enter para seleccionar una opcion");
        attroff(COLOR_PAIR(REDTEXT_DEFAULTBACKGROUND));
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
                    attron(COLOR_PAIR(WHITETEXT_BLUEBACKGROUND));
                    printw("%s", menuOptions[i].data());
                    attroff(COLOR_PAIR(WHITETEXT_BLUEBACKGROUND));
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
                        cin.ignore();
                        enterToContinue();
                        break;
                    }
                    case DELETE_ALL_AGENTS: {
                        string deleteAgents;
                        printw("Esta seguro? (S/N): ");
                        deleteAgents = inputString();
                        if(deleteAgents == "s" || deleteAgents == "S"){
                            agentListRef->deleteAll();
                            cin.ignore();
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
                        printw("Opcion invalida");
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