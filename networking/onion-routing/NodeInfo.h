/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

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