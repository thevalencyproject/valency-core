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