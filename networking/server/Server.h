/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#ifndef SERVER_H
#define SERVER_H

#ifdef __linux__ || __unix__ || __OpenBSD__ || __FreeBSD__ || __NetBSD__ || __APPLE__    // UNIX Implementation
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


class Server {
private:
    bool running;

    sockaddr_in hint;
    int hintSize;

    int listeningSocket;
    std::vector<int> clientSockets;

    fd_set currentSockets, readySockets;
    int setSize = FD_SETSIZE + 1;

    char buffer[4096];

    bool createSocket(int* port);
    bool acceptConnection();                     // Accepts/Denies an Incoming connection request on the listening socket

    bool handleConnection(int clientSocket, std::string (*communicate)(std::string));     // Modify this function to achieve your desired outcomes!

public:
    Server();
    ~Server();

    std::string errorLog;           // If anything fails, this will automatically be set to the relevant error message
    std::string connectionLog;      // If a connection fails, this will automatically be set to the relevant error message

    bool run(int* port, std::string (*communicate)(std::string));
    void stop();
};

#elif WIN32 || _WIN32 || __WIN32__ || __NT__    // Windows Implementation

#endif
#endif