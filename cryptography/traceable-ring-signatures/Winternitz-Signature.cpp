#include "Winternitz-Signature.h"


void WinternitzSignature::hashMessage(char* message) {
    std::string hashedmessage = sha.hash(message);
    std::copy(hashedmessage.begin(), hashedmessage.end(), messageHash);
}

void WinternitzSignature::generatePrivateKey(size_t seed, unsigned char* privateKey) {
    size_t min = 0;
    size_t max = 256;
    for(int i = 0; i < 256; i++)
        privateKey[i] = (unsigned char)random.getRandomNumber(&min, &max, &seed);
}

void WinternitzSignature::generatePublicKey(unsigned char* privateKey, unsigned char* publicKey) {
    int multiple = 0;
    for(int i = 0; i < 16; i++) {

        // Get the segment that needs to be hashed 256 times
        char segment[] = "                ";
        for(int j = 0; j < 16; j++) {
            segment[j] = privateKey[multiple];
            multiple++;
        }

        // Hash the segment 256 times
        std::string hashOutput;
        for(int j = 0; j < 256; j++) {
            hashOutput = sha.hash(segment);
            std::strcpy(segment, hashOutput.c_str());
        }

        // Copy it to the end of the public key array
        int temp = multiple - 16;
        for(int j = 0; j < 16; j++) {
            publicKey[temp] = segment[temp];
            temp++;
        }
    }
}

void WinternitzSignature::generateSignature(unsigned char* message, unsigned char* privateKey, unsigned char* signature) {for(int i = 0; i < 16; i++) {
        // Calculate the hash amount
        int hashAmount;
        hashAmount = 256 - static_cast<int>(message[i]);

        // Get the next 16 bytes of the array
        char segment[] = "                ";
        for(int j = i * 16; j < (16 + (i * 8)); j++)
            segment[j - (i * 16)] = privateKey[j];

        // Hash the corresponding 16 byte sequence of the privateKey array hashAmount times
        std::string hashOutput;
        for(int j = 0; j < hashAmount; j++) {
            hashOutput = sha.hash(segment);
            std::strcpy(segment, hashOutput.c_str());
        }

        // Copy it to the end of the signature array
        for(int j = i * 16; j < (16 + (i * 8)); j++)
            signature[j] = segment[j - (i * 16)];
    }
}