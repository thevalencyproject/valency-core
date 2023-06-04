#include "Server.h"


// Modify this function to achieve your desired outcomes!
bool Server::handleConnection(int clientSocket) {
    int bytesRecv;

    while(1) {
        memset(buffer, 0, 4096);    // Clear the buffer

        // Wait for a message
        bytesRecv = recv(clientSocket, buffer, 4096, 0);
        switch(bytesRecv) {
        case -1:
            connectionLog = "Connection Issue";
            return 1;
        case 0:
            connectionLog = "Client Disconnected";
            return 1;
        }

        // Do something with the message - this line uses iostream - remove it from the header if not in use
        std::cout << "Received: " << std::string(buffer, 0, bytesRecv) << std::endl;
        send(clientSocket, buffer, bytesRecv + 1, 0);   // Resend the message back to the client
    }

    return 0;
}


// Constructor and destructor clear everything for security purposes
Server::Server() {
    stop();
}
Server::~Server() {
    stop();
}

bool Server::createSocket(int port) {
    listeningSocket = socket(AF_INET, SOCK_STREAM, 0);  //IPv4
    if(listeningSocket == -1) {
        errorLog = "Error creating socket";
        return 1;
    }

    // Bind the listening socket to an IP address and port
    memset(&hint, 0, hintSize);                         // Zero the hint
    hint.sin_family = AF_INET;                          // Specify an IPv4 Type
    hint.sin_port = htons(port);                        // Specify the port
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);      // Sets any available IP Address
    if(bind(listeningSocket, (sockaddr*)&hint, sizeof(hint)) == -1) {
        errorLog = "";
        return 1;
    }

    // Mark the socket for being able to be listened on
    if(listen(listeningSocket, SOMAXCONN) == -1) {
        errorLog = "Error listening on the socket - Max Connections may have been reached";
        return 1;
    }

    hintSize = sizeof(hint);    // Set the hint size;
    return 0;
}

bool Server::acceptConnection() {
    // Accept the connection
    int clientSocket = accept(listeningSocket, (sockaddr*)&hint, (socklen_t*)&hintSize);

    FD_SET(clientSocket, &currentSockets);      // Add the new connection to the list of connected clients
    clientSockets.push_back(clientSocket);      // Add the clientSocket to the client vector
}

bool Server::run(int port) {
    if(createSocket(port) == 1)     // Create a listening socket
        return 1;
    
    running = true;

    FD_SET(listeningSocket, &currentSockets);   // Initialise the currentSockets set

    while(running == 1) {
        readySockets = currentSockets;  // readySockets acts as a copy of currentSockets - select() is destructive

        // Run the select() function - stop the server if there is an error
        if(select(setSize, &readySockets, NULL, NULL, NULL) == -1) {
            stop();
            errorLog = "Error running the select() function";
            return 1;
        } else {
            // Go through each socket - if new connection request, run acceptConnection(), else: handleConnection()
            for(int i = 0; i < clientSockets.size(); i++) {
                if(FD_ISSET(i, &readySockets)) {
                    acceptConnection();
                } else {
                    handleConnection(clientSockets[i]);
                }
            }
        }
    }

    return 0;
}

void Server::stop() {
    running = 0;

    FD_ZERO(&currentSockets);       // Zero the currentSockets set
    FD_ZERO(&readySockets);         // Zero the readySockets set

    clientSockets.clear();          // Clear all clients
    listeningSocket = 0;            // Deactivate the listening socket

    memset(buffer, 0, 4096);        // Zero the message buffer
    memset(&hint, 0, hintSize);     // Zero the hint
    hintSize = 0;                   // Zero the hint size
}