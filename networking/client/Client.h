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

    bool communicate();     // Modify this function to achieve your desired outcomes!

public:
    Client();
    ~Client();

    std::string errorLog;   // If anything fails, this will automatically be set to the relevant error message

    bool connectToServer(std::string* ip, int* port);
    void disconnect();
};

#endif