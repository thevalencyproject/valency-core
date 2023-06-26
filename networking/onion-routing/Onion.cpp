#include "Onion.h"


Onion::Onion(int strength) {
    switch(strength) {
    case 1:
        aesSize = 192;
        ntruSize = 1;
        break;
    case 2:
        aesSize = 256;
        ntruSize = 3;
        break;
    case 3:
        aesSize = 256;
        ntruSize = 5;
        break;
    default:
        aesSize = 256;
        ntruSize = 3;
    }
}

std::string Onion::createOnion(std::vector<NodeInfo> nodes, std::string data) {
    AESEncryption aes = AESEncryption(aesSize);
    NTRUencrypt ntru = NTRUencrypt(ntruSize);

    std::string output = data;

    std::string generatedKey;
    for(int i = 0; i < nodes.size(); i++) {
        // Generate a random index for each character of the aes key, and set the character to the corresponding index from data
        size_t dataSize = (size_t)data.size();
        for(int i = 0; i < 32; i++) {
            size_t currentTime = (size_t) std::time(0);
            size_t index = r.getRandomNumber(0, &dataSize, &currentTime);
            generatedKey = generatedKey + data[index];
        }

        // Push the newly generated key into the keys vector and clear temporary variables
        aesKeys.push_back(generatedKey);
        generatedKey.clear();

        // Create the layer by adding the next node's network location to the data, and encrypting with the AES key we just generated
        // the AES key is then encrypted using NTRUencrypt and the cipher is appended to the AES encrypted data 
        output = aes.encrypt(aesKeys[i], std::to_string(nodes[nodes.size() - i].location.port) + " " + nodes[nodes.size() - i].location.address + output);
        output = ntru.encrypt(nodes[nodes.size() - i].address, aesKeys[i]) + " " + output;
    }

    return  output;
}

template<typename T>
void Onion::onionRouting(std::vector<NodeInfo> nodes, std::string data, std::string (T::*communicate)(std::string)) {
    std::string onion = createOnion(nodes, data);
    c.connectToServer(nodes[0].location.address, nodes[0].location.port, communicate, onion);
}