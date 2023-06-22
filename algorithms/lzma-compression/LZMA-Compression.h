#ifndef LZMACOMPRESSION_H
#define LZMACOMPRESSION_H

#include <string>
#include <vector>


struct DictionaryEntry {
    std::string word;
    int code;

    DictionaryEntry() {};
    DictionaryEntry(std::string w, int c) { word = w; code = c; };
};

class LZMACompression {
private:
    std::vector<DictionaryEntry> dictionary;

public:
    LZMACompression();

    std::string compress(std::string *decompressedData);
    std::string decompress(std::string *compressedData);
};

#endif