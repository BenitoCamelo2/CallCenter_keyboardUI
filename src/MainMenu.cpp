#include "../include/MainMenu.h"

MainMenu::MainMenu() {
    agentList = new AgentList();
    splashScreen();
    AgentMenu(new AgentList);
}

void MainMenu::splashScreen() {
    printw("INICIO\n");
    printw("Administracion del call center\n\n");
    printw("Ingresa una tecla para continuar...\n");
    getch();
}
