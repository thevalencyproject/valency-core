#include "FileWriter.h"


void FileWriter::createFile(std::string *data, std::string *path) {
    std::ofstream file;     // Initialising an instance of ofstream to create the file

    file.open(*path);        // Opening the file using the ofstream instance
    file << *data;           // Adding the inputted data string to the file
    file.close();           // Closing the file
}

void FileWriter::createFile(std::vector<std::string> data, std::string *path) {
    std::string formattedData;      // Initialising a string to hold the formatted data
    std::ofstream file;             // Initialising an instance of ofstream to craete the file

    //Turning the vector into a string
    for(int i = 0; i < data.size(); i++) {
        formattedData = formattedData + data[i] + "\n";
    }

    file.open(*path);            // Opening the file using the ofstream instance
    file << formattedData;      // Adding the formatted data string to the file
    file.close();               // Closing the file
}