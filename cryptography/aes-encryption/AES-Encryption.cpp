/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#include "AES-Encryption.h"


void AESEncryption::checkPadding(std::vector<unsigned char> data) {
    int remainder = data.size() % 16;

    for(int i = 0; i < remainder; i++)
        data.push_back(' ');
}

void AESEncryption::keyExpansion() {
    expandedKeys.resize((keySize + 1) * rounds);                     // Create space for the expanded key
    for(int i = 0; i < keySize; i++) { expandedKeys[i] = key[i]; }   // The first 16 bytes are the original key

    int bytesGenerated = keySize;                  // Keep track of the bytes created
    int rConIteration = 1;                         // RCon iteration begins at 1
    unsigned char temp[4];                         // Temporary storage for the 4 byte manipulation in the core expansion algorithm
    int bytesToGenerate = (rounds + 1) * keySize;    // The max number of bytes to generate (dependant on key size)

    while(bytesGenerated < bytesToGenerate) {   // Generation Loop
        // Add the previously generated 4 bytes and add them to the temp array
        for(int i = 0; i < 4; i++)
            temp[i] = expandedKeys[i + bytesGenerated - 4];

        // Perform the core expansion once per key
        if(bytesGenerated % keySize == 0) {
            unsigned int* q = (unsigned int*) temp;
            *q = (*q >> 8) | ((*q & 0xff) << 24);

            // S-Box Four Bytes:
            temp[0] = rijndaelSBox[temp[0]];
            temp[1] = rijndaelSBox[temp[1]];
            temp[2] = rijndaelSBox[temp[2]];
            temp[3] = rijndaelSBox[temp[3]];
            temp[0] ^= rCon[rConIteration];
            rConIteration++;
        }

        // XOR temp with [bytesGenerated - keySize], and store it in expandedKeys
        for(unsigned char i = 0; i < 4; i++) {
            expandedKeys[bytesGenerated] = expandedKeys[bytesGenerated - keySize] ^ temp[i];
            bytesGenerated++;
        }
    }
}

void AESEncryption::addRoundKey() {
    for(int i = 0; i < 16; i++)
        state[i] ^= roundKey[i];
}

void AESEncryption::subBytes() {
    for(int i = 0; i < 16; i++)
        state[i] = rijndaelSBox[state[i]];
}

void AESEncryption::inverseSubBytes() {
    for(int i = 0; i < 16; i++)
        state[i] = invRijndaelSBox[state[i]];
}

void AESEncryption::shiftRows() {
    unsigned char tempState[16];    // Initialise a temporary state array to do the shifting in

    tempState[0] = state[0];        // Shift first row
    tempState[1] = state[5];        //
    tempState[2] = state[10];       //
    tempState[3] = state[15];       //
    
    tempState[4] = state[4];        // Shift second row
    tempState[5] = state[9];        //
    tempState[6] = state[14];       //
    tempState[7] = state[3];        //
    
    tempState[8] = state[8];        // Shift third row
    tempState[9] = state[13];       //
    tempState[10] = state[2];       //
    tempState[11] = state[7];       //
    
    tempState[12] = state[12];      // Shift fourth row
    tempState[13] = state[1];       //
    tempState[14] = state[6];       //
    tempState[15] = state[11];      //

    // Overwrite state with tempState
    memcpy(state, tempState, sizeof(state));
}

void AESEncryption::unShiftRows() {     // The opposite of shiftRows ;)
    unsigned char tempState[16];
    
    tempState[0] = state[0];
    tempState[5] = state[1];        
    tempState[10] = state[2];       
    tempState[15] = state[3];       
    tempState[4] = state[4];
    
    tempState[9] = state[5];        
    tempState[14] = state[6];       
    tempState[3] = state[7];        
    tempState[8] = state[8];
    
    tempState[13] = state[9];       
    tempState[2] = state[10];       
    tempState[7] = state[11];       
    tempState[12] = state[12];
    
    tempState[1] = state[13];       
    tempState[6] = state[14];       
    tempState[11] = state[15];      

    memcpy(state, tempState, sizeof(state));
}

void AESEncryption::mixColumns() {
    unsigned char tempState[16];    // Initialise a temporary state array to do the mixing in

    tempState[0] = (unsigned char)(multiplyBy2[state[0]] ^ multiplyBy3[state[1]] ^ state[2] ^ state[3]);
    tempState[1] = (unsigned char)(state[0] ^ multiplyBy2[state[1]] ^ multiplyBy3[state[2]] ^ state[3]);
    tempState[2] = (unsigned char)(state[0] ^ state[1] ^ multiplyBy2[state[2]] ^ multiplyBy3[state[3]]);
    tempState[3] = (unsigned char)(multiplyBy3[state[0]] ^ state[1] ^ state[2] ^ multiplyBy2[state[3]]);  

    tempState[4] = (unsigned char)(multiplyBy2[state[4]] ^ multiplyBy3[state[5]] ^ state[6] ^ state[7]);
    tempState[5] = (unsigned char)(state[4] ^ multiplyBy2[state[5]] ^ multiplyBy3[state[6]] ^ state[7]);
    tempState[6] = (unsigned char)(state[4] ^ state[5] ^ multiplyBy2[state[6]] ^ multiplyBy3[state[7]]);
    tempState[7] = (unsigned char)(multiplyBy3[state[4]] ^ state[5] ^ state[6] ^ multiplyBy2[state[7]]);  

    tempState[8] = (unsigned char)(multiplyBy2[state[8]] ^ multiplyBy3[state[9]] ^ state[10] ^ state[11]);
    tempState[9] = (unsigned char)(state[8] ^ multiplyBy2[state[9]] ^ multiplyBy3[state[10]] ^ state[11]);
    tempState[10] = (unsigned char)(state[8] ^ state[9] ^ multiplyBy2[state[10]] ^ multiplyBy3[state[11]]);
    tempState[11] = (unsigned char)(multiplyBy3[state[8]] ^ state[9] ^ state[10] ^ multiplyBy2[state[11]]); 

    tempState[12] = (unsigned char)(multiplyBy2[state[12]] ^ multiplyBy3[state[13]] ^ state[14] ^ state[15]);
    tempState[13] = (unsigned char)(state[12] ^ multiplyBy2[state[13]] ^ multiplyBy3[state[14]] ^ state[15]);
    tempState[14] = (unsigned char)(state[12] ^ state[13] ^ multiplyBy2[state[14]] ^ multiplyBy3[state[15]]);
    tempState[15] = (unsigned char)(multiplyBy3[state[12]] ^ state[13] ^ state[14] ^ multiplyBy2[state[15]]);

    // Overwrite state with tempState
    memcpy(state, tempState, sizeof(state));
}

AESEncryption::AESEncryption(int size) {
    switch(size) {
    case 128: rounds = 9; keySize = 16; break;
    case 192: rounds = 11; keySize = 24; break;
    case 256: rounds = 13; keySize = 32; break;
    }
}
AESEncryption::~AESEncryption() {
    data.clear();           //
    key.clear();            // Clear sensitive data
    expandedKeys.clear();   //
}

std::vector<unsigned char> AESEncryption::encrypt(std::vector<unsigned char> k, std::vector<unsigned char> d) {
    std::vector<unsigned char> output;  // Temporary vector to hold encryption output
    
    key = k;
    data = d;

    checkPadding(data);

    int repeat = data.size() / 16;
    int completedBytes = 0;

    keyExpansion();     // Expand the key into separate keys that are used for each round

    for(int i = 0; i < repeat; i++) {
        for(int j = 0; j < 16; j++) { state[i] = data[completedBytes + j]; }    // Set state to next 16 bytes

        addRoundKey();                      // Initial Round
        for(int j = 0; j < rounds; j++) {   // Main Rounds
            subBytes();
            shiftRows();
            mixColumns();
            addRoundKey();
        }
        subBytes();                          //
        shiftRows();                         // Final Round
        addRoundKey();                       //

        for(int j = 0; j < 16; j++) { output.push_back(state[j]); }     // Add the 16 byte section to output
        completedBytes = completedBytes + 16;
    }

    // Append the number of repeats that must be done to decrypt the cipher
    output.insert(output.begin(), '.');
    std::string outputHeader = std::to_string(repeat);
    for(int i = outputHeader.size(); i > 0; i++)
        output.insert(output.begin(), outputHeader[i]);

    // Clear sensitive data and return the output
    data.clear();
    key.clear();
    expandedKeys.clear();
    return output;
}

std::string AESEncryption::encrypt(std::string k, std::string d) {
    std::vector<unsigned char> key;
    for(int i = 0; i < k.size(); i++)
        key.push_back(k[i]);
    
    std::vector<unsigned char> data;
    for(int i = 0; i < d.size(); i++)
        data.push_back(d[i]);
    
    std::vector<unsigned char> vect = encrypt(key, data);
    std::string output(vect.begin(), vect.end());
    return output;
}

std::vector<unsigned char> AESEncryption::decrypt(std::vector<unsigned char> k, std::vector<unsigned char> d) {
    std::vector<unsigned char> output;

    key = k;
    data = d;

    // Read the header (number of repeats) - stored from the start of the vector to the first '.' char
    int repeat;
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '.') {
            std::string repeatTemp(data.begin(), data.begin() + (i - 1));
            repeat = stoi(repeatTemp);
            data.erase(data.begin(), data.begin() + i);
        }
    }

    keyExpansion();     // Expand the keys

    // Decrypt the data
    int completedBytes = 0;
    for(int i = 0; i < repeat; i++) {
        for(int j = 0; j < 16; j++) { state[i] = data[completedBytes + j]; }    // Set state to next 16 bytes

        // Final Round
        addRoundKey();
        unShiftRows();
        inverseSubBytes();

        for(int j = 0; j < rounds; j++) {   // Main Rounds
            addRoundKey();
            mixColumns();
            unShiftRows();
            inverseSubBytes();
        }

        addRoundKey();  // Initial Round

        for(int j = 0; j < 16; j++) { output.push_back(state[j]); }     // Add the 16 byte section to output
        completedBytes = completedBytes + 16;
    }

    data.clear();
    key.clear();
    expandedKeys.clear();
    return output;
}

std::string AESEncryption::decrypt(std::string k, std::string d) {
    std::vector<unsigned char> key;
    for(int i = 0; i < k.size(); i++)
        key.push_back(k[i]);
    
    std::vector<unsigned char> data;
    for(int i = 0; i < d.size(); i++)
        data.push_back(d[i]);
    
    std::vector<unsigned char> vect = decrypt(key, data);
    std::string output(vect.begin(), vect.end());
    return output;
}