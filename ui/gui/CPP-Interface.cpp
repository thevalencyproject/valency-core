/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#include "CPP-Interface.h"


template<typename T>
void CPPInterface::run(int localPort, std::vector<std::string (T::*)(std::string)> funcs) {
    port = localPort;
    functions = funcs;
    server.run(&port, communicate);
}

std::string CPPInterface::communicate(std::string input) {
    int funcIndex = stoi(input.substr(0, 3));   // Calculate the function to use
    input.erase(0, 3);

    return functions[funcIndex](input);         // Run the function and pass through the return
}