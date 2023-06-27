#ifndef JSINTERFACE_H
#define JSINTERFACE_H

#include <string>


class JSInterface {
private:
    std::string htmlPath, jsPath;

public:
    JSInterface() {};

    // Takes in the path to the UI javascript and HTML path - HTML interfaces with JS which interfaces with C++
    void setup(std::string htmlFilePath, std::string jsFilePath);

    // Runs the interface - this detects inputs and sends outputs through JS.
    void run();
    void stop();
};

#endif