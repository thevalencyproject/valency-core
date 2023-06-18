#ifndef NODEINFO_H
#define NODEINFO_H

#include "NetworkLocation.h"


struct NodeInfo {
    NetworkLocation location;
    std::string address;

    NodeInfo() {};
    NodeInfo(NetworkLocation l, std::string a) {
        set(l, address);
    };

    // Sets the Address
    void set(NetworkLocation l, std::string a) {
        location = l;
        address = a;
    }
};

#endif