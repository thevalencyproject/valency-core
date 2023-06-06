#ifndef NTRUENCRYPT_H
#define NTRUENCRYPT_H

#include <string>


class NTRUencrypt {
private:
    int bits;

public:
    NTRUencrypt(int strength);
    ~NTRUencrypt();

    std::string generatePublicKey(std::string privateKey);  // Public Key Generator
    std::string generatePrivateKey(int seed);               // Private Key Generator

    std::string encrypt(std::string privateKey, std::string receiverKey, std::string data);
    std::string decrypt(std::string privateKey, std::string receiverKey, std::string data);
};

#endif