#include <WinSock2.h>

#include <iostream>
#include <list>

#include "msg.h"

#include "computer_info.h"

using std::cerr;
using std::cout;
using std::endl;

#define ERROR -1

typedef struct {
    SOCKET player;
    unsigned int ID;
} connection;

std::list<connection> playerList;

bool loop = true;
int count = 0;

bool initialize_comuniactions() {
    WSADATA getDataWS;
    int waserr = WSAStartup(MAKEWORD(2, 2), &getDataWS);

    if (waserr != 0) {
        cerr << "Error; Libreria Winsock no encontrada!" << endl;

        return false;
    }

    cout << "Libreria Winsock encontrada con exito." << endl;
    cout << "Estado del servidor: " << getDataWS.szSystemStatus << endl;

    if (LOBYTE(getDataWS.wVersion) != 2 || HIBYTE(getDataWS.wVersion) != 2) {
        cerr << "Error; Libreria Winsock no soporta la version 2.0!" << endl;
        WSACleanup();

        return false;
    }

    return true;
}

SOCKET create_socket() {
    SOCKET setSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (setSocket == INVALID_SOCKET) {
        cerr << "Error al crear el socket: " << WSAGetLastError() << "!" << endl;
        WSACleanup();

        return ERROR;
    }

    cout << "Socket creado con exito." << endl;

    return setSocket;
}

bool bind_socket(const char* IP, SOCKET getSocket) {
    sockaddr_in localDir;
    
    memset(&localDir, 0, sizeof(sockaddr_in));

    localDir.sin_family = AF_INET;
    localDir.sin_port = htons(INADDR_ANY);
    localDir.sin_addr.s_addr = inet_addr(IP);
    
    if (bind(getSocket, (sockaddr*)&localDir, sizeof(localDir)) == SOCKET_ERROR) {
        cerr << "Error en bind_socket(): " << WSAGetLastError() << "!" << endl;
        WSACleanup();

        return false;
    }

    cout << "bind_socket() realizado con exito." << endl;
    cout << "\tIP: " << inet_ntoa(localDir.sin_addr) << endl;
    cout << "\tPort: " << localDir.sin_port << endl;

    return true;
}

bool listen_socket(SOCKET getSocket) {
    if (listen(getSocket, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Error al escuchar al socket: " << WSAGetLastError() << "!" << endl;
        WSACleanup();

        return false;
    }

    cout << "Socket escuchando. Esperando a conexiones entrantes..." << endl;

    return true;
}

SOCKET accept_entrance(SOCKET getSocket) {
    cout << "Esperando a un cliente para conectar..." << endl;
    cout << "*** SERVIDOR LISTO PARA CONECTAR ***" << endl;

    SOCKET newSocket = SOCKET_ERROR;

    while (loop && newSocket == SOCKET_ERROR) {
        newSocket = accept(getSocket, NULL, NULL);
    }

    cout << "Cliente conectado con exito." << endl;

    return newSocket;
}

int get_data(char* buffer, int length, SOCKET getSocket) {
    int bytes = SOCKET_ERROR;
    bytes = recv(getSocket, buffer, length, NULL);

    if (bytes == SOCKET_ERROR) {
        cerr << "Error en recv(): " << WSAGetLastError() << "!" << endl;

        return ERROR;
    }

    return bytes;
}

void close_comunications(SOCKET connection) {
    closesocket(connection);
    WSACleanup();

    loop = false;
}

void exit_server() {
    char c;

    while (loop) {
        std::cin >> c;

        if (c == 'q') loop = false;
    }
}

int send_data(SOCKET getSocket, const char* buffer, int length) {
    cout << "Enviando mensage: " << buffer << "..." << endl;

    int bytes = send(getSocket, buffer, length, NULL);

    cout << "Bytes enviados: " << bytes << endl;

    return bytes;
}

void send_to_all(Message& data, int notMe) {
    std::list<connection>::iterator it;

    for (it = playerList.begin(); it != playerList.end(); it++) {
        if (it->ID != notMe) {
            cout << "Reenviando mensage..." << endl;

            send_data(it->player, (char*)&data, sizeof(data));
        }
    }
}

int create_player(SOCKET getSocket) {
    connection player;

    player.ID = count++;
    player.player = getSocket;

    playerList.push_back(player);

    return player.ID;
}

void attend_player(SOCKET data) {
    unsigned int ID = create_player(data);

    cout << "Nuevo jugador creado: " << ID << endl;

    Message message;

    if (get_data((char*)&message, sizeof(message), data) != ERROR) send_to_all(message, ID);

    closesocket(data);
}

int main() {
    SOCKET connect, data;

    if (!initialize_comuniactions()) {
        system("pause");

        return ERROR;
    }

    connect = create_socket();

    if (connect == ERROR) {
        cerr << "Error; Socket no creado!" << endl;
        system("pause");

        return ERROR;
    }

    if (!bind_socket(COMPUTER_IP, connect)) {
        system("pause");

        return ERROR;
    }

    while (loop) {
        if (!listen_socket(connect)) {
            system("pause");

            return ERROR;
        }

        data = accept_entrance(connect);
    }

    closesocket(connect);
    WSACleanup();

    return 0;
}