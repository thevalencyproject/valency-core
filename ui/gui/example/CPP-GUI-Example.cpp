/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#include "CPP-GUI-Example.h"


std::string CPPGUIExample::login(std::string input) {       // Custom Login Function
    if(input == "userpassword") {
        return "1";
    }
    return "0";
}
std::string CPPGUIExample::calculator(std::string input) {  // Custom Calculator Function
    std::string firstNum;
    std::string secondNum;
    for(int i = 0; i < input.size(); i++) {     // Get both inputs
        if(input[i] == ' ') {
            firstNum = input.substr(0, i - 1);
            secondNum = input.substr(i + 1, input.size());
        }
    }

    // Check if the input is a number
    if((!firstNum.empty() && std::find_if(firstNum.begin(), firstNum.end(), [](unsigned char c) { return !std::isdigit(c); }) == firstNum.end()) && 
    (!secondNum.empty() && std::find_if(secondNum.begin(), secondNum.end(), [](unsigned char c) { return !std::isdigit(c); }) == secondNum.end())) {
        int result = stoi(firstNum) + stoi(secondNum);
        return std::to_string(result);
    }

    return "The input is not a number!";
}

template<typename T>
void CPPGUIExample::run(int port) {
    // Create and fill the vectors with the custom functions
    std::vector<std::string (T::*)(std::string)> functions;
    functions.push_back(login);
    functions.push_back(calculator);

    interface.run(port, functions);     // Run the C++ Interface
}