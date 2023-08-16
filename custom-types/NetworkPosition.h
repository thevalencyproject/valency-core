/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

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