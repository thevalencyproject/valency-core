#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <vector>
#include <string>
#include <fstream>


class FileWriter {
public:
    FileWriter() {}

    // Creates/Overwrites a file - takes in the filepath (if craeting a new file, ass the filename + extension to the filepath)
    void createFile(std::string *data, std::string *path);
    void createFile(std::vector<std::string> data, std::string *path);
};

#endif