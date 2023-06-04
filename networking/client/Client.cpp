#include "Client.h"


// Modify this function to achieve your desired outcomes!
bool Client::communicate() {
    std::string message = "https://youtu.be/xm3YgoEiEDc";   // Test message ;)

    while(1) {
        // Send something to the server
        if(send(commSocket, message.c_str(), message.size() + 1, 0) == -1) {
            errorLog = "Error sending data to the server";
            return 1;
        }

        // Clear the buffer and wait for a response
        memset(buffer, 0, 4096);
        receivedBytes = recv(commSocket, buffer, 4096, 0);
        
        // Display the received data - this line uses iostream - remove it from the header if not in use
        std::cout << "[RECEIVED FROM SERVER]: " << std::string(buffer, receivedBytes) << std::endl;

        // Change the message and repeat - this example implementation changes message based on server response
        if(std::string(buffer, receivedBytes) == "TEST RESPONSE") {
            message = "TEST MESSAGE";
        } else {
            message = "/quit";
        }

        // Stop communicating if the message is '/quit'
        if(message == "/quit")
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

bool Client::connectToServer(std::string* ip, int* port) {
    if(createSocket(*ip, port) == 1 || initialiseConnection() == 1)
        return 1;
    
    return communicate();
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