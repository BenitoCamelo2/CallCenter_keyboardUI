cmake_minimum_required(VERSION 3.21)
project(keyboard_input)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)

add_executable(keyboard_input
        src/main.cpp
        src/Agent.cpp
        src/AgentList.cpp
        src/AgentMenu.cpp
        src/AgentNode.cpp
        src/AgentNodeException.cpp
        src/Client.cpp
        src/ClientList.cpp
        src/ClientMenu.cpp
        src/ClientNode.cpp
        src/Date.cpp
        src/main.cpp
        src/MainMenu.cpp
        src/Name.cpp
        src/Time.cpp
        src/util.cpp)

target_link_libraries(keyboard_input ncurses)