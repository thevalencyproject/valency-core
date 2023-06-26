#ifndef CLIENT_H
#define CLIENT_H

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

#endif