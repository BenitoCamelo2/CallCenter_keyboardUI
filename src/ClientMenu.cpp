#include "../include/ClientMenu.h"
#include "../include/AgentMenu.h"
#include "../include/util.h"

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

ClientMenu::ClientMenu(ClientList *clientList): clientListRef(clientList) {
    //inicializes main menu
    mainClientMenu();
}

void ClientMenu::enterToContinue() {
    cout << "Presione enter para continuar..." << endl;
    getchar();
}

void ClientMenu::addClient() {
    //temp data to incorporate into a client to add to the list
    Client tempClient;
    int minute, hour, year, day, month;
    string clientPhoneNumber;
    Time clientCallDuration, clientCallStart;
    Date clientCallDate;

    //Entrance of data
    system(CLEAR);
    cout << "AGREGAR CLIENTE" << endl;
    cout << "Numero telefonico: ";
    cin.ignore();getline(cin, clientPhoneNumber);

    //verification of phone number length
    while(clientPhoneNumber.length() < 10){
        cout << "Ingresa de nuevo: ";
        getline(cin, clientPhoneNumber);
    }

    //register of start time, with verification
    cout << "Hora de inicio de llamada: ";
    cin >> hour;
    cout << "Minuto de inicio de llamada: ";
    cin >> minute;
    while(!clientCallStart.setData(hour, minute)){
        cout << "Ingresa la hora de nuevo: ";
        cin >> hour;
        cout << "Ingresa el minuto de nuevo: ";
        cin >> minute;
    }

    //register of call duration, with verification
    cout << "Horas de duracion de llamada: ";
    cin >> hour;
    cout << "Minutos de duracion de llamada: ";
    cin >> minute;
    while(!clientCallDuration.setData(hour, minute)){
        cout << "Ingresa la hora de nuevo: ";
        cin >> hour;
        cout << "Ingresa el minuto de nuevo: ";
        cin >> minute;
    }

    //register of the call date, with verification
    cout << "Anio de llamada: ";
    cin >> year;
    cout << "Mes de llamada: ";
    cin >> month;
    cout << "Dia de llamada: ";
    cin >> day;
    while(!clientCallDate.setData(year, month, day)){
        cout << "Ingresa de nuevo" << endl;
        cout << "Anio de llamada: ";
        cin >> year;
        cout << "Mes de llamada: ";
        cin >> month;
        cout << "Dia de llamada: ";
        cin >> day;
    }

    tempClient.setData(clientPhoneNumber, clientCallStart, clientCallDuration, clientCallDate);
    clientListRef->insertOrdered(tempClient);
}

void ClientMenu::deleteClient() {
    Client tempClient1 = Client();
    ClientNode* tempClientNode;
    string phoneNumber;

    //creation of temp client to find and delete the desired one
    cout << "ELIMINAR CLIENTE" << endl;
    //prints client to find the client
    printClients();
    cout << "Numero telefonico: ";
    cin.ignore();getline(cin, phoneNumber);
    while(phoneNumber.length() > 10){
        cout << "Ingresa de nuevo: ";
        getline(cin, phoneNumber);
    }

    //assign phone number
    tempClient1.setPhoneNumber(phoneNumber);

    //search client by phone number and get list position
    tempClientNode = clientListRef->retrievePos(tempClient1, 1);

    //if the client is found, it has a valid position, or else its a nullptr
    if(tempClientNode != nullptr){
        //prints client data and verifies the deletion
        char exit = '\0';
        clientListHeader();
        printClient(tempClientNode);
        cout << "Esta seguro que quiere eliminar el cliente? (N/S): ";
        cin >> exit;
        cin.ignore();
        if(exit == 'S' || exit == 's'){
            //deletes
            clientListRef->deleteData(tempClientNode);
        } else {
            //if client types anything but 's', it will cancel
            enterToContinue();
        }
    } else {
        //client was not found
        cout << "Cliente no encontrado" << endl;
        cin.ignore();
        enterToContinue();
    }
}

void ClientMenu::modifyClient() {
    Client tempClient1 = Client();
    ClientNode* tempClientNode;
    string phoneNumber;

    //modifying of a client
    system(CLEAR);
    cout << "MODIFICAR CLIENTE" << endl << endl;
    clientListHeader();
    printClients(); //prints clients for user to choose
    cout << "Numero telefonico: ";
    cin.ignore();getline(cin, phoneNumber);
    while(phoneNumber.length() > 10){ //if phone number is longer than 10 digits, it requests to enter data again
        cout << "Ingresa de nuevo: ";
        getline(cin, phoneNumber);
    }
    tempClient1.setPhoneNumber(phoneNumber);
    //finds the client position
    tempClientNode = clientListRef->retrievePos(tempClient1, 1);
    //if the client is not found, it returns nullptr
    if(tempClientNode != nullptr){
        //choose what to change
        int opc;
        system(CLEAR);
        cout << "MODIFICAR " << tempClientNode->getData().getPhoneNumber() << endl;
        cout << "Seleccionar una opcion para modificar: " << endl;
        cout << "1. Numero telefonico" << endl;
        cout << "2. Fecha de la llamada" << endl;
        cout << "3. Hora inicio de la llamada" << endl;
        cout << "4. Duracion de la llamada" << endl;
        cout << "0. Cancelar" << endl;
        cout << "Opcion: ";
        cin >> opc;
        switch(opc){
            //modify the phone number
            case MODIFY_PHONE: {
                string clientPhoneNumber;
                tempClient1 = tempClientNode->getData();
                cout << "Numero telefonico nuevo: ";
                cin.ignore();getline(cin, clientPhoneNumber);
                while(clientPhoneNumber.length() > 10){
                    cout << "Ingresa de nuevo: ";
                    getline(cin, clientPhoneNumber);
                }
                tempClient1.setPhoneNumber(clientPhoneNumber);
                break;
            }
            //modify the call date
            case MODIFY_CALL_DATE: {
                Date callDate;
                int year, month, day;
                tempClient1 = tempClientNode->getData();
                cout << "Anio: ";
                cin >> year;
                cout << "Mes: ";
                cin >> month;
                cout << "Dia: ";
                cin >> day;
                callDate.setData(year, month, day);
                tempClient1.setCallDate(callDate);
                break;
            }
            //modify the call start time
            case MODIFY_CALL_START: {
                Time callStart;
                int hour, minute;
                tempClient1 = tempClientNode->getData();
                cout << "Horas: ";
                cin >> hour;
                cout << "Minutos: ";
                cin >> minute;
                callStart.setData(hour, minute);
                tempClient1.setCallStart(callStart);
                break;
            }
            //modify the call duration
            case MODIFY_CALL_DURATION: {
                Time callDuration;
                int hour, minute;
                tempClient1 = tempClientNode->getData();
                cout << "Horas: ";
                cin >> hour;
                cout << "Minutos: ";
                cin >> minute;
                callDuration.setData(hour, minute);
                tempClient1.setCallDuration(callDuration);
                break;
            }
            default: {
                enterToContinue();
                break;
            }
        }
        tempClientNode->setData(tempClient1);
    } else {
        cout << "Cliente no encontrado" << endl;
        cin.ignore();
        enterToContinue();
    }
}

void ClientMenu::searchClient() {
    system(CLEAR);
    int opc;

    //search client, user chooses what to search by
    cout << "BUSCAR CLIENTE" << endl;
    cout << "Buscar por: " << endl;
    cout << "1. Numero telefonico" << endl;
    cout << "2. Fecha" << endl;
    cout << "3. Hora de inicio" << endl;
    cout << "4. Duracion de llamada" << endl;
    cout << "0. Cancelar" << endl;
    cout << "Opcion: ";
    cin >> opc;

    //switch depending on what selected
    switch(opc){
        case SEARCH_BY_PHONENUMBER: {
            string phoneNumber;
            Client tempClient = Client();
            ClientNode* tempClientNode = new ClientNode();
            cout << "Numero telefonico: ";
            cin.ignore();getline(cin, phoneNumber);
            while(phoneNumber.length() > 10){
                cout << "Ingresa de nuevo: ";
                cin >> phoneNumber;
            }
            tempClient.setPhoneNumber(phoneNumber);
            //finds the client and prints the clients data
            tempClientNode = clientListRef->retrievePos(tempClient, 1);
            if(tempClientNode != nullptr){
                tempClient = clientListRef->findData(tempClientNode);
                clientListHeader();
                printClient(tempClientNode);
                cin.ignore();
                enterToContinue();
            } else {
                cout << "Cliente no encontrado" << endl;
                cin.ignore();
                enterToContinue();
            }
            break;
        }
        //search by call date
        case SEARCH_BY_CALLDATE: {
            int year, month, day;
            Date callDate;
            Client tempClient = Client();
            ClientNode* tempClientNode = new ClientNode();
            cout << "Anio: ";
            cin >> year;
            cout << "Mes: ";
            cin >> month;
            cout << "Dia: ";
            cin >> day;
            while(!callDate.setData(year, month, day)){
                cout << "Ingresa el anio de nuevo: ";
                cin >> year;
                cout << "Ingresa el mes de nuevo: ";
                cin >> month;
                cout << "Ingresa el dia de nuevo: ";
                cin >> day;
            }
            tempClient.setCallDate(callDate);
            //finds client and displays data
            tempClientNode = clientListRef->retrievePos(tempClient, 2);
            if(tempClientNode != nullptr){
                tempClient = clientListRef->findData(tempClientNode);
                clientListHeader();
                printClient(tempClientNode);
                cin.ignore();
                enterToContinue();
            } else {
                cout << "Cliente no encontrado" << endl;
                cin.ignore();
                enterToContinue();
            }
            break;
        }
        //search by call date
        case SEARCH_BY_CALLSTART: {
            int hour, minute;
            Time callStart;
            Client tempClient = Client();
            ClientNode* tempClientNode = new ClientNode();
            cout << "Hora: ";
            cin >> hour;
            cout << "Minuto: ";
            cin >> minute;
            while(!callStart.setData(hour, minute)){
                cout << "Ingresa la hora de nuevo: ";
                cin >> hour;
                cout << "Ingresa el minuto de nuevo: ";
                cin >> minute;
            }
            tempClient.setCallStart(callStart);
            //find client data and display the client
            tempClientNode = clientListRef->retrievePos(tempClient, 3);
            if(tempClientNode != nullptr){
                tempClient = clientListRef->findData(tempClientNode);
                clientListHeader();
                printClient(tempClientNode);
                cin.ignore();
                enterToContinue();
            } else {
                cout << "Cliente no encontrado" << endl;
                cin.ignore();
                enterToContinue();
            }
            break;
        }
        //search by call duration
        case SEARCH_BY_CALLDURATION: {
            int hour, minute;
            Time callDuration;
            Client tempClient = Client();
            ClientNode* tempClientNode = new ClientNode();

            cout << "Hora: ";
            cin >> hour;
            cout << "Minuto: ";
            cin >> minute;

            while(!callDuration.setData(hour, minute)){
                cout << "Ingresa la hora de nuevo: ";
                cin >> hour;
                cout << "Ingresa el minuto de nuevo: ";
                cin >> minute;
            }
            tempClient.setCallDuration(callDuration);
            //find the client data and display the data
            tempClientNode = clientListRef->retrievePos(tempClient, 4);
            if(tempClientNode != nullptr){
                tempClient = clientListRef->findData(tempClientNode);
                clientListHeader();
                printClient(tempClientNode);
                cin.ignore();
                enterToContinue();
            } else {
                cout << "Cliente no encontrado" << endl;
                cin.ignore();
                enterToContinue();
            }
            break;
        }
        default: {
            cin.ignore();
            enterToContinue();
        }
    }
}

void ClientMenu::printClient(ClientNode *clientNode) {
    //prints data in this structure:
    //|PhoneNumber|CallDate|CallStart|CallDuration|
    //can always build it some day to calculate when the call ended
    cout << "|" << clientNode->getData().getPhoneNumber();
    cout.width(20 - clientNode->getData().getPhoneNumber().length());
    cout << "|" << clientNode->getData().getCallDate().toString();
    cout.width(20 - clientNode->getData().getCallDate().toString().length());
    cout << "|" << clientNode->getData().getCallStart().toString();
    cout.width(23 - clientNode->getData().getCallStart().toString().length());
    cout << "|" << clientNode->getData().getCallDuration().toString();
    cout.width(20 - clientNode->getData().getCallDuration().toString().length());
    cout << "|" << endl;
}

void ClientMenu::printClients() {
    ClientNode* temp(clientListRef->getFirstPos());
    ClientNode* last(clientListRef->getLastPos());

    //makes sure there are nodes in the list
    if(temp != nullptr) {
        //this is when there is only one client in the list
        if (temp == last) {
            printClient(temp);
            //multiple clients in the list
        } else {
            while (temp != nullptr) {
                printClient(temp);
                temp = temp->getNext();
            }
        }
    } else {
        cout << "No hay clientes en la lista" << endl;
    }
}

void ClientMenu::mainClientMenu() {
    bool terminate = false;
    int HEIGHT, LENGTH;
    int key = '\0';
    int option = 0;

    string menuOptions[CLIENT_MENU_OPTIONS] = {
            "   Agregar cliente               ",
            "   Eliminar cliente              ",
            "   Modifcar cliente              ",
            "   Buscar cliente                ",
            "   Mostrar los clientes          ",
            "   Eliminar TODOS los clientes   ",
            "   Regresar                      "
    };

    //color pair for selecting an option
    start_color();
    init_pair(WHITE_TEXT_BLUE_BACKGROUND, COLOR_WHITE, COLOR_CYAN);
    init_pair(RED_TEXT_DEFAULT_BACKGROUND, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_TEXT_DEFAULT_BACKGROUND, COLOR_GREEN, COLOR_BLACK);

    //clear the screen
    clear();
    refresh();

    //main client menu
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
        for(int i = 0; i < CLIENT_MENU_OPTIONS; i++){
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
        switch(key) {
            //option goes up
            case KEY_UP: {
                option--;
                //makes sure option doesn't go farther than options available
                if (option >= CLIENT_MENU_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = CLIENT_MENU_OPTIONS - 1;
                }
                break;
            }
                //option goes down
            case KEY_DOWN: {
                option++;
                if (option >= CLIENT_MENU_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = CLIENT_MENU_OPTIONS - 1;
                }
                break;
            }
                //user selects desired option
            case ENTER: {
                //makes sure option is valid, just in case
                if (option >= CLIENT_MENU_OPTIONS) {
                    option = 0;
                } else if (option < 0) {
                    option = CLIENT_MENU_OPTIONS - 1;
                }
                switch (option) {
                    case ADD_CLIENT: {
                        addClient();
                        break;
                    }
                    case DELETE_CLIENT: {
                        deleteClient();
                        break;
                    }
                    case MODIFY_CLIENT: {
                        modifyClient();
                        break;
                    }
                    case SEARCH_CLIENT: {
                        searchClient();
                        break;
                    }
                    case SHOW_CLIENTS: {
                        system(CLEAR);
                        cout << "MOSTRAR CLIENTES" << endl;
                        clientListHeader();
                        printClients();
                        cin.ignore();
                        enterToContinue();
                        break;
                    }
                    case DELETE_ALL_CLIENTS: {
                        clientListRef->deleteAll();
                        cin.ignore();
                        enterToContinue();
                        break;
                    }
                    case EXIT_CLIENT: {
                        terminate = true;
                        break;
                    }
                    default: {
                        cout << "xd" << endl;
                    }
                }
            }
        }
    }while(!terminate);
}