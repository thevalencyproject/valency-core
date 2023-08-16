/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

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