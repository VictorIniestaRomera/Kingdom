#include <iostream>

#include "log_writer.h"

#include "map_manager.h"
#include "entity_manager.h"

#include "map_writings.h"

#include "map_math.h"

#include "keyboard.h"

#include "player.h"

#include <WinSock2.h>
#include "computer_info.h"

#include "msg.h"

#define CLIENT_ERROR -1

SOCKET connection;
bool connected, end;

Map* map;

bool initialize_comunications() noexcept {
    WSADATA getDataWS;

    int wsaerr = WSAStartup(MAKEWORD(2, 2), &getDataWS);

    if (wsaerr != 0) {
        LogWriter::log("Error; Client -> WinSock library not found!");

        return false;
    }

    std::string l = "Client -> Server state: ";
    l += getDataWS.szSystemStatus;

    LogWriter::log("Client -> WinSock library found.");
    LogWriter::log(l);

    if (LOBYTE(getDataWS.wVersion) != 2 || HIBYTE(getDataWS.wVersion) != 2) {
        LogWriter::log("Error; Client -> WinSock library does not support the corresponding version 2.0!");
        WSACleanup();

        return false;
    }

    return true;
}

SOCKET create_socket() noexcept {
    SOCKET setSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (setSocket == SOCKET_ERROR) {
        std::string error = "Error; Client -> Error at socket(): ";
        error += WSAGetLastError();
        error += "!";

        LogWriter::log(error);
        WSACleanup();

        return CLIENT_ERROR;
    }

    LogWriter::log("Client -> Socket created successfully.");

    return setSocket;
}

bool connect_to_server(const char* IP, SOCKET getSocket) noexcept {
    sockaddr_in localDir;

    memset(&localDir, 0, sizeof(sockaddr_in));

    localDir.sin_family = AF_INET;
    localDir.sin_port = htons(INADDR_ANY);
    localDir.sin_addr.s_addr = inet_addr(IP);

    if (connect(getSocket, (sockaddr*)&localDir, sizeof(localDir)) == SOCKET_ERROR) {
        std::string error = "Error; Client -> Error at connect(): ";
        error += WSAGetLastError();
        error += "!";

        LogWriter::log(error);
        WSACleanup();

        return false;
    }

    LogWriter::log("Client -> Connected to server successfully.");

    return true;
}

int send_data(SOCKET getSocket, const char* BUFFER, int length) noexcept {
    std::string mssg = "Client -> Sending message: ";
    mssg += BUFFER;
    mssg += "...";

    LogWriter::log(mssg);

    int bytes = send(getSocket, BUFFER, length, NULL);

    std::string byt = "Client -> Bytes sent: ";
    byt += bytes;

    LogWriter::log(byt);

    return bytes;
}

int get_data(SOCKET getSocket, char* BUFFER, int length) noexcept {
    int bytes = SOCKET_ERROR;
    bytes = recv(getSocket, BUFFER, length, NULL);

    if (bytes == SOCKET_ERROR) {
        std::string error = "Error; Client -> Error at recv(): ";
        error += WSAGetLastError();
        error += "!";

        LogWriter::log(error);

        return CLIENT_ERROR;
    }

    return bytes;
}

bool accept_petition() noexcept {
    Message mssg;

    char* b = (char*)&mssg;

    get_data(connection, b, sizeof(MSG));

    if (!mssg.type == CONNECT) return false;

    atend_message(mssg);

    return true;
}

bool connect_player(char* IP) noexcept {
    connected = true;

    if (initialize_comunications()) {
        connection = create_socket();

        if (connection != SOCKET_ERROR) {
            if (connect_to_server(IP, connection)) connected = accept_petition();
        }
    }

    return connected;
}

void disconnect_player() noexcept {
    closesocket(connection);

    connected = false;

    Message mssg;
    mssg.disconnect = true;

    const char* b = (const char*)&mssg;

    send_data(connection, b, sizeof(Message));
}

void read_message() noexcept {
    Message mssg;

    while (!end) {
        char* b = (char*)&mssg;

        get_data(connection, b, sizeof(MSG));
        atend_message(mssg);
    }
}

void atend_message(Message mssg) noexcept {
    LogWriter::log("Server -> Attending message...");

    if (mssg.type == CONNECT) {
        LogWriter::log("Server -> Creating new player...");

        Player* p = new Player(mssg.team, map->get_map());

        const char* b = (const char*)&mssg;

        send_data(connection, b, sizeof(MSG));
    }
}

int main() {
    LogWriter::clear();
    LogWriter::log("*** STARTING KINGDOM ***");

    map = new Map(40, 80);

    const char* TEAM_NAME = "one";

    Player* player = new Player(TEAM_NAME, map->get_map());

    map->draw_map();

    std::cout << "Write E to add a new entity.\n";
    std::cout << "Write B to add a new building.\n";

    while (!player->finished()) {
        std::string y_pos, x_pos;

        if (Keyboard::key_pressed() == Key::E) {
            std::cout << "Write Y position to spawn.\n";
            std::cin >> y_pos;

            std::cout << "Write X position to spawn.\n";
            std::cin >> x_pos;

            int i_y_spawn = util::MapMath::calc_pos(y_pos.c_str());
            int i_x_spawn = util::MapMath::calc_pos(x_pos.c_str());
            
            std::cout << "Write W to add a new Woodsman.\n";
            std::cout << "Write B to add a new Builder.\n";

            while (!player->finished()) {
                if (Keyboard::key_pressed() == Key::W) {
                    map->spawn_entity(EntityWritings::WOODS_MAN, TEAM_NAME, util::Point2(i_y_spawn, i_x_spawn));
                    player->switch_finished();
                }
                else if (Keyboard::key_pressed() == Key::B) {
                    map->spawn_entity(EntityWritings::BUILDER, TEAM_NAME, util::Point2(i_y_spawn, i_x_spawn));
                    player->switch_finished();
                }
            }
        }
        else if (Keyboard::key_pressed() == Key::B) {
            std::cout << "Write Y position to build.\n";
            std::cin >> y_pos;

            std::cout << "Write X position to build.\n";
            std::cin >> x_pos;

            int i_y_spawn = util::MapMath::calc_pos(y_pos.c_str());
            int i_x_spawn = util::MapMath::calc_pos(x_pos.c_str());

            std::cout << "Write V to build a Village.\n";
            std::cout << "Write C to build a Control Point.\n";

            while (!player->finished()) {
                if (Keyboard::key_pressed() == Key::V) {
                    map->build_building(ChunkWritings::VILLAGE, TEAM_NAME, util::Point2(i_y_spawn, i_x_spawn));
                    player->switch_finished();
                }
                else if (Keyboard::key_pressed() == Key::C) {
                    map->build_building(ChunkWritings::CONTROL_POINT, TEAM_NAME, util::Point2(i_y_spawn, i_x_spawn));
                    player->switch_finished();
                }
            }
        }
    }

    EntityManager::get_singleton()->update_entities(map->get_map());

    map->draw_map();

    LogWriter::log("*** ALL DONE ***");
    LogWriter::log("Cleaning up...");
}