#ifndef SERVER_H
#define SERVER_H

#if defined (__linux__) || (__OpenBSD__) || (__FreeBSD__) || (__NetBSD__) || (__APPLE__)    // UNIX Header
#include <iostream>
#include <string>
#include <vector>
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

    template<typename T>
    bool run(int* port, std::string (T::*communicate)(std::string));
    void stop();
};


#elif _WIN32    // Windows Header


#endif