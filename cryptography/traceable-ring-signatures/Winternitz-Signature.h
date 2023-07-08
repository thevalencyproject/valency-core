#ifndef WINTERNITZ_SIGNATURE_H
#define WINTERNITZ_SIGNATURE_H

#include <string>
#include <bits/stdc++.h>
#include "Random.h"
#include "SHA256.h"


/* Winternitz Signature Scheme is a One-time signature scheme 
        -> Private Key: unsigned char private[256]
        -> Public Key:  unsigned char public[256]
        -> Message Hash: unsigned char hash[16]
        -> Signature: unsigned char signature[256]
*/
class WinternitzSignature {
private:
    Random random;
    SHA256 sha;

public:
    WinternitzSignature() {};

    void generatePrivateKey(size_t seed, unsigned char* privateKey);
    void generatePublicKey(unsigned char* privateKey, unsigned char* publicKey);
    void generateSignature(unsigned char* message, unsigned char* privateKey, unsigned char* signature);
    std::string generatePrivateKey(size_t seed);
    std::string generatePrivateKey(std::string seed);
    std::string generatePublicKey(std::string privateKey);
    std::string generateSignature(std::string message, std::string privateKey);

    bool validateSignature(unsigned char* signature, unsigned char* message, unsigned char* publicKey);
    bool validateSignature(std::string signature, std::string message, std::string publicKey);
};

#endif