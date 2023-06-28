#include "CPP-Interface.h"


template<typename T>
void CPPInterface::run(int localPort, std::vector<std::string (*)(std::string)> funcs) {
    port = localPort;
    functions = funcs;
    server.run(&port, communicate);
}

std::string CPPInterface::communicate(std::string input) {
    int funcIndex = stoi(input.substr(0, 3));   // Calculate the function to use
    input.erase(0, 3);

    return functions[funcIndex](input);         // Run the function and pass through the return
}