#ifndef RINGSIGNATURE_H
#define RINGSIGNATURE_H

#include <string>
#include <vector>
#include "FileReader.h"
#include "FileWriter.h"


struct RingSignature {
    std::string keyImage;                                 // The key image is the public key generated from a temporary one-time private key
    std::vector<TransactionOutput> transactionOutputs;    // The transaction outputs vector contains the REAL output + all the decoy transactions 
};
struct TransactionOutput {
    // Sender and Receiver Public Keys (both of these should be temporary - generate a new key pair for every transaction)
    std::string senderKey;      // The senders temporary stealth public address
    std::string receiverKey;    // The receivers temporary stealth public address

    std::string prevShardHash;
    std::string prevBlockHash;

    int transactionAmount;      // The amount sent in the transaction (this is temporary until a quantum-proof commitment is implemented)
};

class TraceableRingSignature {
private:
    // Used to read and write to the transaction output repository file
    FileReader reader;
    FileWriter writer;

    // The transaction output repository - contains known transaction outputs
    std::string transactionRepositoryPath;
    std::vector<TransactionOutput> transactionRepository;

    std::vector<TransactionOutput> transactionOutputs;                // The transaction outputs selected for the ring signature
    std::string generateSignature(std::string transactionOutput);     // Creates a single signature using SHA256 on the transactionOutput

public:
    TraceableRingSignature() {};

    RingSignature generateSignature(std::vector<std::string> publicKeyList);
    std::string getOneTimePublicKey();
};

#endif