#ifndef LZMACOMPRESSION_H
#define LZMACOMPRESSION_H

#include <string>
#include <vector>
#include "Position.h"


class LZMACompression {
private:
    size_t dictionarySize;
    std::vector<Position2D> dictionary;
    std::vector<std::pair<int, int>> tuples;

    void initialiseDictionary(std::vector<char> data);                      // Initialises the dictionary with the given size
    std::pair<int, int> findMatch(std::vector<char> sequence);              // Finds the longest match of the given sequence in the dictionary
    void processUnmatchedBytes(std::vector<char> unmatchedBytes);           // Processes the unmatched bytes as literals
    std::pair<int, int> encodeLength(int length);                           // Encodes the given length using LZMA's match length encoding
    int decodeLength(std::pair<int, int> encodedLength);                    // Decodes the given length using LZMA'z match length encoding
    std::vector<char> rangeEncode(std::vector<char> dataStream);            // Encodes the given data stream using range encoding
    std::vector<char> rangeDecode(std::vector<char> encodedDataStream);     // Decodes the given data stream using range encoding

public:
    LZMACompression();

    // Compresses or Decompresses the given data
    std::vector<char> compress(std::vector<char> *inputData);
    std::vector<char> decompress(std::vector<char> *compressedData);
    std::string compress(std::string *inputData);
    std::string decompress(std::string *compressedData);
};

#endif