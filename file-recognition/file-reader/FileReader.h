#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <string>
#include <fstream>


struct FileReader {
    FileReader() {};
    std::string errorLog;

    // Generates a vector with each line of the inputted file from the filepath specified
    std::vector<std::string> getData(std::string* path);
};

#endif