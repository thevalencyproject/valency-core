#ifndef LZMACOMPRESSION_H
#define LZMACOMPRESSION_H

#include <string>
#include <vector>
#include "Position.h"


class LZMACompression {
private:
    std::vector<Position2D> dictionary;
    
public:
    LZMACompression();

    std::string compress(std::string *decompressedData);
    std::string decompress(std::string *compressedData);
};

#endif