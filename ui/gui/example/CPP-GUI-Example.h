/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#ifndef CPPGUIEXAMPLE
#define CPPGUIEXAMPLE

#include <algorithm>
#include "CPP-Interface.h"


class CPPGUIExample {
private:
    CPPInterface interface;     // The interface (the server that communicates with the JavaScript)

    // Custom Functions
    std::string login(std::string input);
    std::string calculator(std::string input);

public:
    CPPGUIExample() {};

    template<typename T>
    void run(int port);
};

#endif