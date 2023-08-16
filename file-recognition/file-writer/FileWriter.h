/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <vector>
#include <string>
#include <fstream>


struct FileWriter {
    FileWriter() {};

    // Creates/Overwrites a file - takes in the filepath (if creating a new file, add the filename + extension to the filepath)
    void createFile(std::string *data, std::string *path);
    void createFile(std::vector<std::string> data, std::string *path);
};

#endif