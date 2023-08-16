/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#ifndef ONIONNODE_H
#define ONIONNODE_H

#include <string>
#include <vector>
#include "Client.h"
#include "Server.h"
#include "NodeInfo.h"
#include "NTRUencrypt.h"
#include "AES-Encryption.h"


class OnionNode {
private:
    int port;

    std::string pubKey;
    std::string privKey;

    Client client;
    Server server;

    std::string communicate(std::string);

public:
    OnionNode(int p);

    void initialise(std::string publicKey, std::string privateKey);
    void run();
    void stop();
};

#endif