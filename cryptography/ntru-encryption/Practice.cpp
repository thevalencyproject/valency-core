#include "NTRUencrypt.h"
#include "NTRUencrypt.cpp"
#include <iostream>

int main() {
    NTRUencrypt ntru = NTRUencrypt(4);
    int seed = 654987165;
    std::string privateKey = ntru.generatePrivateKey(seed);
    std::cout << "Private Key" << std::endl << privateKey << std::endl << std::endl << std::endl;// << publicKey;

    std::string publicKey = ntru.generatePublicKey(privateKey);
    std::cout << "Public Key" << std::endl << publicKey << std::endl;// << publicKey;

    std::string data = "JoeBidenJoeBidenJoeBidenJoeBidenJoeBiden";
    std::string output = ntru.encrypt(publicKey, data);
    std::cout << "ENCRYPTED CIPHER: " << std::endl << output << std::endl; 

    return 0;
}