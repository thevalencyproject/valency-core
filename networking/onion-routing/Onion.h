#ifndef ONION_H
#define ONION_H

#include <ctime>
#include <vector>
#include <string>
#include "Random.h"
#include "NodeInfo.h"
#include "NTRUencrypt.h"
#include "AES-Encryption.h"


class Onion {
private:
    int aesSize;    // 128, 196, or 256 -> see AES-Encryption.h for more details
    int ntruSize;   // 0 - 7 -> see NTRUencrypt.h for details

    Random r;       // Used to generate the AES key for each node

    std::vector<std::string> aesKeys;
    void generateAESKeys(std::vector<NodeInfo> nodes, std::string data);

public:
    Onion(int strength);

    // The final destination location (where the last node should send the data) should be the final network location in the nodes vector (address doesnt matter)
    std::string createOnion(std::vector<NodeInfo> nodes, std::string data);
};

#endif