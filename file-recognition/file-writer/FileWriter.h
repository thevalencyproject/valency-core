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