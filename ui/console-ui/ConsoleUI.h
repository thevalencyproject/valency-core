#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <cmath>
#include <string>
#include <vector>
#include <iostream>


class ConsoleUI {
private:
    /*  These are the ui styles:
            0. Box
            1. Minimalistic
            2. Hyphen 
            3. Arrow
        This style is selected on initialisation.
        The default style is Box.                 */
    int style = 0;

    // Prints a string with proper spacing for each style
    void boxFormatting(std::string msg);
    void boxFormatting(std::vector<std::string> msg);
    void minimalistFormatting(std::string msg);
    void minimalistFormatting(std::vector<std::string> msg);
    void hyphenFormatting(std::string msg);
    void hyphenFormatting(std::vector<std::string> msg);
    void arrowFormatting(std::string msg);
    void arrowFormatting(std::vector<std::string> msg);

    std::string getInput();     // Returns the input from the user

public:
    ConsoleUI() {}
    ConsoleUI(int s);       // Specify the style of the ui - 0=Box, 1=Minimalistic, 2=Hyphen, 3=Arrow
    ~ConsoleUI() {}

    void setStyle(int style);   // Changes styles - if style wasn't specified in construction or if you want to change style

    void header(std::vector<std::string> title);     // Produces a header in the selected style with the inputted title
    void footer();                                   // Produces a footer in the selected style

    template <typename T>
    void message(T msg);          // Displays a message (single-line and multi-line): takes in a string or vector string
    template <typename T>
    std::string input(T msg);     // Displays a message and returns a string from the user (single-line and multi-line): takes in a string or vector string

    int menu(std::vector<std::string> options, bool closed);    // Displays a menu - input the options as each vector index and if the menu has a closed top. Returns the user input
};

#endif