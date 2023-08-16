/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#ifndef CLIENT_H
#define CLIENT_H

#if defined (__linux__) || (__OpenBSD__) || (__FreeBSD__) || (__NetBSD__) || (__APPLE__)    // UNIX Header
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>


class Client {
private:
    bool connected;
    int commSocket;
    sockaddr_in hint;

    // Message Buffer
    char buffer[4096];  
    int receivedBytes;

    bool createSocket(std::string ip, int* port);
    bool initialiseConnection();

    bool handleConnection(std::string (*communicate)(std::string), std::string initialMessage);

public:
    Client();
    ~Client();

    std::string errorLog;   // If anything fails, this will automatically be set to the relevant error message

    // Communicate using your own custom function pointer - The initial message is what is first sent to the server
    template<typename T>
    bool connectToServer(std::string* ip, int* port, std::string (T::*communicate)(std::string), std::string initialMessage);
    void disconnect();
};


#elif _WIN32    // Windows Header


#endif