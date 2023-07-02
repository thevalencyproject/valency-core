#include "Ring-Signature.h"


void TraceableRingSignature::readPublicKeyRepository() {
    publicKeyRepository = reader.getData(&publicKeyRepositoryPath);
}

std::string TraceableRingSignature::generateSignature(TransactionData data, std::string privateKey) {
    std::string sigInput = data.receiverKey + std::to_string(data.transactionAmount);
    return winternitz.generateSignature(sigInput, privateKey);
}

void TraceableRingSignature::writeToPublicKeyRepository(std::vector<std::string> publicKeys) {
    readPublicKeyRepository();                                                                      // Ensure the existing keys are in place
    publicKeyRepository.insert(publicKeyRepository.end(), publicKeys.begin(), publicKeys.end());    // Append the new keys
    writer.createFile(publicKeyRepository, &publicKeyRepositoryPath);                               // Write the file
}

RingSignature TraceableRingSignature::generateRingSignature(unsigned int amount, std::string receiver, std::string privateKey, unsigned short decoys) {
    switch(decoys) { case 4: break; case 5: break; case 6: break; default: decoys = 5; }                 // Ensure decoys are in range

    // Select the decoy addresses (uses the private key as a secure seed for the randomness)
    std::vector<std::string> pubKeys;
    std::vector<std::string> tempKeys = publicKeyRepository;
    for(int i = 0; i < decoys; i++) {
        int r = random.getRandomNumber(0, (size_t*)tempKeys.size(), (size_t*)atoi(privateKey.data()));   // Generate a random number within range
        pubKeys.push_back(tempKeys[r]);                                                                  // Add the decoy key
        tempKeys.erase(tempKeys.begin() + r);                                                            // Erase the key from temp
    }

    TransactionData info;
    info.receiverKey = receiver;
    info.transactionAmount = amount;

    RingSignature output;
    output.data = info;
    output.publicKeys = pubKeys;
    output.keyImage = sha.hash((char*)privateKey.c_str());
    output.signature = generateSignature(info, privateKey);

    return output;
}

std::string TraceableRingSignature::generateOneTimePrivateKey(size_t seed) {
    return winternitz.generatePrivateKey(seed);
}

std::string TraceableRingSignature::generateOneTimePublicKey(std::string privateKey) {
    return winternitz.generatePublicKey(privateKey);
}