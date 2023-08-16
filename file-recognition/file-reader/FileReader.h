/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

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