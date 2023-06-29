#ifndef CPPINTERFACE_H
#define CPPINTERFACE_H

#include <string>
#include <vector>
#include "Server.h"


class CPPInterface {
private:
    int port;
    Server server;   // The server that passes through information from JS and C++

    std::string communicate(std::string input);
    std::vector<std::string (*)(std::string)> functions;

public:
    CPPInterface() {};

    // Runs the interface - this detects inputs and sends outputs through JS by hosting a server which acts as a middleman.
    // The Function Pointer Vector contains the functions that are run when the a message is received by the JS script
    //   -> the functions are run depending on what the first 3 bytes of the received message is (000 = 1st func, 001 = 2nd func, ..., 201 = 202nd func)
    //   -> the string that the function returns is what is sent back to the JS script
    template<typename T>
    void run(int localPort, std::vector<std::string (T::*)(std::string)> funcs);
};

#endif