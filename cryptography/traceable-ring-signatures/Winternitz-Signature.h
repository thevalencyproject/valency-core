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

    unsigned char messageHash[16];              // The hashed message (hashed using SHA256) (this is 16 characters [256 bit])
    void hashMessage(char* message);            // Hashes the message and stores it in messageHash

public:
    WinternitzSignature() {};

    void generatePrivateKey(size_t seed, unsigned char* privateKey);
    void generatePublicKey(unsigned char* privateKey, unsigned char* publicKey);
    void generateSignature(unsigned char* message, unsigned char* privateKey, unsigned char* signature);

    bool validateSignature(unsigned char* signature, unsigned char* message);
};

#endif