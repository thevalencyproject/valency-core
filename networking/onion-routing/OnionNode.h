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

    Client c;
    Server s;

    std::vector<std::string> clientIdentifier;
    std::string communicate(std::string data);

public:
    OnionNode(int p);

    void initialise(std::string publicKey, std::string privateKey);
    void run();
    void stop();
};

#endif