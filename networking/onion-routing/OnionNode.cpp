#include "OnionNode.h"


std::string OnionNode::communicate(std::string data) {
    NTRUencrypt ntru = NTRUencrypt(3);
    AESEncryption aes = AESEncryption(256);

    std::string ip;
    int port;
    std::string aesKey;
    
    // Find the NTRUencrypted AESKey Cipher and Decrypt it to get the AES Key
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == ' ') {
            aesKey = ntru.decrypt(privKey, data.substr(0, i - 1));      // Decrypt the AES key using NTRUencrypt
            data.erase(0, i);                                           // Remove the key cipher from the input data:
            break;
        }
    }

    std::string decrypted = aes.decrypt(aesKey, data);      // Decrypt the layer of the onion using the AES Key

    // Find the IP address and Port from the decrypted layer
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == ' ') {
            ip = data.substr(0, i - 1);
            for(int j = i; i < data.size(); i++) {
                if(data[i] == ' ') {
                    port = stoi(data.substr(i, j - 1));
                    data.erase(0, j);
                }
            }

            break;
        }
    }

    std::string (OnionNode::*blank)(std::string);   // Using a blank message communication function, as we do not need to communicate

    // Send the data to the next node in the network and tell the previous node/client to disconnect
    client.connectToServer(&ip, &port, blank, data);
    return "/quit";
}

OnionNode::OnionNode(int p) {
    port = p;
}

void OnionNode::initialise(std::string publicKey, std::string privateKey) {
    stop();     // Ensure the node isn't running
    
    pubKey = pubKey;
    privKey = privKey;
}

void OnionNode::run() {
    // Set up the communicate() function pointer and run the server
    std::string (OnionNode::*comm)(std::string) = communicate;
    server.run(&port, comm);
    stop();
}

void OnionNode::stop() {    // Clear everything
    int port = 0;
    pubKey.clear();
    privKey.clear();
}