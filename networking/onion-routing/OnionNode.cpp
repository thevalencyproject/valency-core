#include "OnionNode.h"


std::string communicate(std::string data) {

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
    clientIdentifier.clear();
}