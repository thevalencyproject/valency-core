#include "FileReader.h"

std::vector<std::string> FileReader::getData(std::string* path) {
    std::string line;
    std::vector<std::string> data;

    // Open the file stream
    std::ifstream file(*path);
    if(file.is_open()) {
        // Push back each line from the file into the vector
        while(std::getline(file, line))
            data.push_back(line);

    } else { errorLog = "Error reading from data stream"; }

    return data;
}