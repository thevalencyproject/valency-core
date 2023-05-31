#ifndef NETWORKLOCATION_H
#define NETWORKLOCATION_H

#include <string>


// Contains a port and network address - used for connections
struct NetworkLocation {
    int port;
    std::string address;

    NetworkLocation() {};
    NetworkLocation(int p, std::string ip) {
        set(p, ip);
    }

    // Sets the Address
    void set(int p, std::string ip) {
        port = p;
        address = ip;
    }
};

#endif