#include "ConsoleUI.h"


ConsoleUI::ConsoleUI(int s) {
    switch(style) {
    case 1: style = 1; 
        break;
    case 2: style = 2;
        break;
    case 3: style = 3;
        break;
    default: style = 0;
    }
}

std::string ConsoleUI::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleUI::boxFormatting(std::string msg) {
    // Calculating spacing on either side:
    int rightSpace = ceil((30 - msg.size()) / 2);
    int leftSpace = rightSpace;
    if((rightSpace * 2) + msg.size() != 30) { leftSpace = leftSpace - 1; }

    // Left Spacing
    std::cout << "|";
    for(int j = 0; j < leftSpace; j++) { std::cout << " "; }

    std::cout << msg;   // Display the input message

    // Right Spacing
    for(int j = 0; j < rightSpace; j++) { std::cout << " "; }
    std::cout << "|" << std::endl;
}
void ConsoleUI::boxFormatting(std::vector<std::string> msg) {
    for(int i = 0; i < msg.size(); i++) {
        // Calculating spacing on either side:
        int rightSpace = ceil((30 - msg[i].size()) / 2);
        int leftSpace = rightSpace;
        if((rightSpace * 2) + msg[i].size() != 30) { leftSpace = leftSpace - 1; }

        // Left Spacing
        std::cout << "|";
        for(int j = 0; j < leftSpace; j++) { std::cout << " "; }

        std::cout << msg[i];    // Display the input message

        // Right Spacing
        for(int j = 0; j < rightSpace; j++) { std::cout << " "; }
        std::cout << "|" << std::endl;
    }
}
void ConsoleUI::minimalistFormatting(std::string msg) {
    std::cout << msg << std::endl;
}
void ConsoleUI::minimalistFormatting(std::vector<std::string> msg) {
    for(int i = 0; i < msg.size(); i++) { std::cout << msg[i] << std::endl; }
}
void ConsoleUI::hyphenFormatting(std::string msg) {
    std::cout << "- " + msg << std::endl;
}
void ConsoleUI::hyphenFormatting(std::vector<std::string> msg) {
    for(int i = 0; i < msg.size(); i++) { std::cout << "- " + msg[i] << std::endl; }
}
void ConsoleUI::arrowFormatting(std::string msg) {
    std::cout << "-> " + msg << std::endl;
}
void ConsoleUI::arrowFormatting(std::vector<std::string> msg) {
    for(int i = 0; i < msg.size(); i++) { std::cout << "-> " + msg[i] << std::endl; }
}

void ConsoleUI::header(std::vector<std::string> title) {
    switch(style) {
    case 0:
        std::cout << " ______________________________ " << std::endl;
        std::cout << "|                              |" << std::endl;
        boxFormatting(title);
        std::cout << "|______________________________|" << std::endl;
        break;

    case 1:
        for(int i = 0; i < title.size(); i++) { 
            std::cout << title[i] << std::endl;
        }
        std::cout << std::endl;
        break;

    case 2:
        for(int i = 0; i < title.size(); i++) {
            std::cout << "- " + title[i] << std::endl;
        }
        std::cout << std::endl;
        break;

    case 3: 
        for(int i = 0; i < title.size(); i++) {
            std::cout << "-> " + title[i] << std::endl;
        }
        std::cout << std::endl;
        break;
    }
}
void ConsoleUI::footer() {
    switch(style) {
    case 0:
        std::cout << " ______________________________ " << std::endl;
        std::cout << "|                              |" << std::endl;
        std::cout << "|        EXITED PROGRAM        |" << std::endl;
        std::cout << "|______________________________|";
        break;

    case 1:
        std::cout << "EXITED PROGRAM";
        break;

    case 2:
        std::cout << "- EXITED PROGRAM -";
        break;

    case 3:
        std::cout << "-> EXITED PROGRAM <-";
        break;
    }
}

template <typename T>
void ConsoleUI::message(T msg) {
    switch(style) {
    case 0:
        std::cout << " ______________________________ " << std::endl;
        std::cout << "|                              |" << std::endl;
        boxFormatting(msg);
        std::cout << "|______________________________|" << std::endl;
        break;

    case 1: 
        minimalistFormatting(msg);
        std::cout << std::endl;
        break;

    case 2: 
        hyphenFormatting(msg);
        std::cout << std::endl;
        break;

    case 3: 
        arrowFormatting(msg);
        std::cout << std::endl;
        break;
    }
}

template <typename T>
std::string ConsoleUI::input(T msg) {
    switch(style) {
    case 0:
        std::cout << " ______________________________ " << std::endl;
        std::cout << "|                              |" << std::endl;
        boxFormatting(msg);
        std::cout << "|______________________________|" << std::endl;
        std::cout << std::endl;
        std::cout << "    -> ";
        break;
    case 1: 
        minimalistFormatting(msg);
        std::cout << std::endl << ": ";
        break;
    case 2: 
        hyphenFormatting(msg);
        std::cout << std::endl << "- ";
        break;
    case 3: 
        arrowFormatting(msg);
        std::cout << std::endl << "-> ";
        break;
    }

    return getInput();
}

bool ConsoleUI::yesOrNo(bool closed) {
    switch(style) {
    case 0:
        if(closed) {
            std::cout << " ______________________________ " << std::endl;
        }
        std::cout << "|                              |" << std::endl;
        std::cout << "|   1. Yes                     |" << std::endl;
        std::cout << "|   2. No                      |" << std::endl;
        std::cout << "|______________________________|" << std::endl;
        std::cout << std::endl << "    -> ";
        break;

    case 1:
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;
        std::cout << std::endl << ": ";
        break;

    case 2:
        std::cout << "1 - Yes" << std::endl;
        std::cout << "2 - No" << std::endl;
        std::cout << std::endl << "- ";
        break;

    case 3:
        std::cout << " -> 1. Yes" << std::endl;
        std::cout << " -> 2. No" << std::endl;
        std::cout << std::endl << "-> ";
        break;
    }

    if(getInput() == "1")
        return 1;

    return 0;
}

int ConsoleUI::menu(std::vector<std::string> options, bool closed) {
    switch(style) {
    case 0:
        if(closed) {
            std::cout << " ______________________________ " << std::endl;
        }
        std::cout << "|                              |" << std::endl;
        std::cout << "|  Please Select One:          |" << std::endl;

        for(int i = 0; i < options.size(); i++) {
            std::cout << "|   " + std::to_string(i+1) + ". " + options[i];
            
            // Finds the difference between the total space and the number of spaces on the left + the length of the message + the number of digits in the index (i+1)
            for(int j = 0; j < ((5 + options[i].size() + ((i+1) > 0 ? (int) log10 ((double) (i+1)) + 1 : 1)) - 30); j++) {
                std::cout << " ";
            }
            std::cout << "|" << std::endl;
        }

        std::cout << "|______________________________|" << std::endl;
        std::cout << std::endl << "    -> ";
        break;

    case 1:
        std::cout << "Please Select One:" << std::endl;
        for(int i = 0; i < options.size(); i++) {
            std::cout << std::to_string(i+1) + ". " + options[i] << std::endl;
        }
        std::cout << std::endl << ": ";
        break;

    case 2:
        std::cout << "- Please Select One:" << std::endl;
        for(int i = 0; i < options.size(); i++) {
            std::cout << std::to_string(i+1) + " - " + options[i] << std::endl;
        }
        std::cout << std::endl << "- ";
        break;

    case 3:
        std::cout << "-> Please Select One:" << std::endl;
        for(int i = 0; i < options.size(); i++) {
            std::cout << std::to_string(i+1) + " -> " + options[i] << std::endl;
        }
        std::cout << std::endl << "-> ";
        break;
    }

    return stoi(getInput());
}