#include "Winternitz-Signature.h"


void WinternitzSignature::generatePrivateKey(size_t seed, unsigned char* privateKey) {
    size_t max = 256;
    for(int i = 0; i < 256; i++)                                                    // Loop over the size of the private key
        privateKey[i] = (unsigned char)random.getRandomNumber(0, &max, &seed);      // Get a random char between 0 and 256
}

void WinternitzSignature::generatePublicKey(unsigned char* privateKey, unsigned char* publicKey) {
    char segment[] = "";
    for(int i = 0; i < 16; i++) {
        std::copy(privateKey + (i * 16), privateKey + ((i + 1) * 16), segment);     // Get the segment that needs to be hashed 256 times
        
        for(int j = 0; j < 256; j++)
            std::strcpy(segment, sha.hash(segment).c_str());                        // Hash the segment 256 times

        std::copy(segment, segment + ((i + 1) * 16), publicKey + (i * 16));         // Copy the segment into the output
    }
}

void WinternitzSignature::generateSignature(unsigned char* message, unsigned char* privateKey, unsigned char* signature) {
    int hashRepeat;
    char segment[] = "";
    for(int i = 0; i < 16; i++) {
        std::copy(privateKey + (i * 16), privateKey + ((i + 1) * 16), segment);     // Get the segment that needs to be hashed
        hashRepeat = 256 - static_cast<int>(message[i]);                            // Calculate the number of times the segment will be hashed

        for(int j = 0; j < hashRepeat; j++)
            std::strcpy(segment, sha.hash(segment).c_str());                        // Hash the segment the calculated number of times

        std::copy(segment, segment + ((i + 1) * 16), signature + (i * 16));         // Copy the segment into the output
    }
}

bool WinternitzSignature::validateSignature(unsigned char* signature, unsigned char* message, unsigned char* publicKey) {
    unsigned char messageHash[16];     // The hashed message
    unsigned char output[256];         // The output of the verification algorithm - checked against public key

    std::strcpy((char*) messageHash, (char*)sha.hash((char*)message).c_str());   // Hash the message

    int hashRepeat;
    char segment[] = "";
    for(int i = 0; i < 16; i++) {
        std::copy(signature + (i * 16), signature + ((i + 1) * 16), segment);    // Get the segment that needs to be hashed
        hashRepeat = 256 - static_cast<int>(messageHash[i]);                     // Calculate the number of times the segment will be hashed

        for(int j = 0; j < hashRepeat; j++)
            std::strcpy(segment, sha.hash(segment).c_str());                     // Hash the segment the calculated number of times

        std::copy(segment, segment + ((i + 1) * 16), output + (i * 16));         // Copy the segment into the output
    }

    if(output == publicKey)    // Check signature validity by comparing with public key
        return true;
    
    return false;
}