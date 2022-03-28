#ifndef PROGRAMA_AGENTMENU_H
#define PROGRAMA_AGENTMENU_H

#include <iostream>
#include <ncurses/ncurses.h>

#include "AgentList.h"

#define AGENT_MENU_OPTIONS 8
#define AGENT_MODIFY_OPTIONS 9

using namespace std;

class AgentMenu {
private:
    AgentList* agentListRef;
    static void enterToContinue();
    //add an agent
    void addAgent();
    //delete an agent
    void deleteAgent();
    //modify any attribute of an agent
    void modifyAgent();
    //search an agent by any attribute
    void searchAgent();
    //sort agent, either by name or specialty
    void sortAgents();
    //print one agent
    static void printAgent(AgentNode* agentNode);
    static void printClient(ClientNode* clientNode);
    //print all the agents
    void printClients(AgentNode* agentNode);
    void printAgents(const string& option);
    //main menu
    void mainAgentMenu();
public:
    explicit AgentMenu(AgentList* agentList);
};

enum{
    SEARCH_CODE = 1,
    SEARCH_LAST_NAME,
    SEARCH_HOUR_START,
    SEARCH_HOUR_END,
    SEARCH_EXTENSION,
    SEARCH_SPECIALTY,
    EXIT_SEARCH
};

enum{
    ADD_AGENT = 0,
    DELETE_AGENT,
    MODIFY_AGENT,
    SEARCH_AGENT,
    SORT_AGENTS,
    SHOW_AGENTS,
    DELETE_ALL_AGENTS,
    EXIT_AGENT
};

enum {
    MODIFY_CODE = 0,
    MODIFY_NAME,
    MODIFY_START_TIME,
    MODIFY_END_TIME,
    MODIFY_EXTENSION,
    MODIFY_EXTRA_HOURS,
    MODIFY_SPECIALTY,
    MODIFY_CLIENTS,
    EXIT_MODIFY
};

enum{
    SERVIDORES = 1,
    ESCRITORIO,
    PORTATILES,
    LINUX,
    IMPRESORAS,
    REDES
};


#endif //PROGRAMA_AGENTMENU_H
