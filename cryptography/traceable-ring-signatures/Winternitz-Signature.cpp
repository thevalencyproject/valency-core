#include "Winternitz-Signature.h"


void WinternitzSignature::hashMessage(char* message) {
    std::string hashedmessage = sha.hash(message);
    std::copy(hashedmessage.begin(), hashedmessage.end(), messageHash);
}

void WinternitzSignature::generatePrivateKey(size_t seed, unsigned char* privateKey) {
    size_t max = 256;
    for(int i = 0; i < 256; i++)                                                    // Loop over the size of the private key
        privateKey[i] = (unsigned char)random.getRandomNumber(0, &max, &seed);      // Get a random char between 0 and 256
}

void WinternitzSignature::generatePublicKey(unsigned char* privateKey, unsigned char* publicKey) {
    char segment[] = "";
    for(int i = 0; i < 16; i++) {
        std::copy(privateKey + (i * 16), privateKey + ((i + 1) * 16), segment);     // Get the segment that needs to be hashed 256 times
        
        std::string hash;
        for(int j = 0; j < 256; j++) {
            hash = sha.hash(segment);                                               // Hash the segment 256 times
            std::strcpy(segment, hash.c_str());
        }

        std::copy(segment, segment + ((i + 1) * 16), publicKey + (i * 16));         // Copy the segment into the output
    }
}

void WinternitzSignature::generateSignature(unsigned char* message, unsigned char* privateKey, unsigned char* signature) {
    int hashRepeat;
    char segment[] = "";
    for(int i = 0; i < 16; i++) {
        std::copy(privateKey + (i * 16), privateKey + ((i + 1) * 16), segment);     // Get the segment that needs to be hashed
        hashRepeat = 256 - static_cast<int>(message[i]);                            // Calculate the number of times the segment will be hashed

        std::string hashOutput;
        for(int j = 0; j < hashRepeat; j++) {
            hashOutput = sha.hash(segment);                                         // Hash the segment the calculated number of times
            std::strcpy(segment, hashOutput.c_str());
        }

        std::copy(segment, segment + ((i + 1) * 16), signature + (i * 16));         // Copy the segment into the output
    }
}

bool WinternitzSignature::validateSignature(unsigned char* signature, unsigned char* message, unsigned char* publicKey) {
    unsigned char output[256];   // The output of the verification algorithm - checked against public key
    char bareMessage[] = "";     // The unhashed message, converted to char for use in the hash function

    std::copy(message, message + sizeof(message), bareMessage);     // Copy unsigned char message to char
    hashMessage(bareMessage);                                       // messageHash now contains the hashed message

    int hashRepeat;
    char segment[] = "";
    for(int i = 0; i < 16; i++) {
        std::copy(signature + (i * 16), signature + ((i + 1) * 16), segment);   // Get the segment that needs to be hashed
        hashRepeat = 256 - static_cast<int>(messageHash[i]);                    // Calculate the number of times the segment will be hashed

        std::string hashOutput;
        for(int j = 0; j < hashRepeat; j++) {
            hashOutput = sha.hash(segment);                                     // Hash the segment the calculated number of times
            std::strcpy(segment, hashOutput.c_str());
        }

        std::copy(segment, segment + ((i + 1) * 16), output + (i * 16));        // Copy the segment into the output
    }

    if(output == publicKey)    // Check signature validity by comparing with public key
        return true;
    
    return false;
}