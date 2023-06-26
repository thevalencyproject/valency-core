#include "Client.h"


// Modify this function to achieve your desired outcomes!
bool Client::handleConnection(std::string (*communicate)(std::string), std::string initialMessage) {
    int counter = 0;
    std::string message = initialMessage;
    if(initialMessage == "")
        std::string message = "https://youtu.be/xm3YgoEiEDc";   // Default Message :)
    

    while(1) {
        // Send something to the server
        if(counter == 0) {      // Send the first message to the server to start communications
            if(send(commSocket, message.c_str(), message.size() + 1, 0) == -1) {
                errorLog = "Error sending data to the server";
                return 1;
            }

            counter++;
        } else {
            if(send(commSocket, message.c_str(), message.size() + 1, 0) == -1) {
                errorLog = "Error sending data to the server";
                return 1;
            }
        }

        // Clear the buffer and wait for a response
        memset(buffer, 0, 4096);
        receivedBytes = recv(commSocket, buffer, 4096, 0);
        
        // Use the input function to determine what the reply
        message = communicate(std::string(buffer, receivedBytes));
        
        if(message == "/quit")  // Stop communicating if the message is '/quit'
            break;
    }

    disconnect();   // Disconnect from the server
    return 0;
}


// Constructor and destructor clear everything for security purposes
Client::Client() {
    disconnect();
}
Client::~Client() {
    disconnect();
}

template<typename T>
bool Client::connectToServer(std::string* ip, int* port, std::string (T::*communicate)(std::string), std::string initialMessage) {
    if(createSocket(*ip, port) == 1 || initialiseConnection() == 1)
        return 1;
    
    return handleConnection(communicate);
}

bool Client::createSocket(std::string ip, int* port) {
    commSocket = socket(AF_INET, SOCK_STREAM, 0);   // Initialise the socket and check for errors
    if(commSocket == -1) {
        errorLog = "Error creating the communication socket";
        return 1;
    }

    // Initialise the hint
    hint.sin_family = AF_INET;                          // Specify an IPv4 Type
    hint.sin_port = htons(*port);                        // Specify the port
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);     // Specify the IP Address

    return 0;
}

bool Client::initialiseConnection() {
    if(connect(commSocket, (sockaddr*)&hint, sizeof(hint)) == -1) {
        errorLog = "Error connecting to the server";
        return 1;
    }

    connected = 1;
    return 0;
}

void Client::disconnect() {
    connected = 0;

    close(commSocket);                  // Close the socket
    commSocket == 0;                    // Zero the socket

    memset(buffer, 0, 4096);            // Zero the message buffer
    memset(&hint, 0, sizeof(hint));     // Zero the hint
}