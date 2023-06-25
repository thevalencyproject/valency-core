#include "LZMA-Compression.h"


void LZMACompression::initialiseDictionary(size_t size) {
    dictionarySize = size;
    dictionary.clear();
    dictionary.resize(size, 0);
}

std::pair<int, int> LZMACompression::findMatch(std::vector<char> sequence, size_t position) {
    int matchingDistance = 0;
    int matchingLength = 0;

    for(size_t i = 0; i < dictionary.size(); i++) {
        size_t length = 0;

        while(position + length < sequence.size() && i + length < dictionary.size() && sequence[position + length] == dictionary[i + length])
            length++;
        
        if(length > matchingLength) {
            matchingDistance = dictionary.size() - i;
            matchingLength = length;
        }
    }

    return std::make_pair(matchingDistance, matchingLength);
}

std::vector<char> LZMACompression::processUnmatchedBytes(std::vector<char> unmatchedBytes) {
    std::vector<char> output;
    std::map<char, float> probabilities;

    for(char c : unmatchedBytes)    // Count occurence of each byte
        probabilities[c]++;
    
    for(auto& p : probabilities)    // Convert counts to probabilities
        p.second /= unmatchedBytes.size();

    // Perform range encoding on the unmatched bytes: here, it is simplified to just scaling the character's ASCII value by probability
    for(char c : unmatchedBytes)    // Will be changed out for a more robust range encoding function in the future
        output.push_back(static_cast<char>(c * probabilities[c]));
    
    return output;
}

std::pair<int, int> LZMACompression::encodeLength(int length) {
    return std::make_pair(length / 2, length % 2);  // Simple length encoding for now
}

int LZMACompression::decodeLength(std::pair<int, int> encodedLength) {
    return encodedLength.first / 2;
}

std::map<char, float> LZMACompression::calculateSymbolProbabilities(std::vector<char> dataStream) {
    std::map<char, float> probabilities;

    for(char c : dataStream)        // Count the occurence of each byte
        probabilities[c]++;

    for(auto& p : probabilities)    // Convert counts to probabilities
        p.second /= dataStream.size();
    
    return probabilities;
}

std::vector<char> LZMACompression::rangeEncode(std::vector<char> dataStream) {
    std::vector<char> output;
    unsigned int low = 0;
    unsigned int range = static_cast<unsigned int>(-1);

    std::map<char, float> probabilities = calculateSymbolProbabilities(dataStream);     // Get the probability of each symbol

    for(char symbol : dataStream) {
        // Calculate the range for the symbol based on the probabilities
        unsigned int scale = range;
        unsigned int high = low + static_cast<unsigned int>(scale * probabilities[symbol]);
        range = high - low;

        // Update the low value based on the cumulative probability of the symbols
        float cumulativeProbability = 0;
        for(auto& p : probabilities) {
            if(p.first == symbol)
                break;

            cumulativeProbability += p.second;
        }

        low += static_cast<unsigned int>(scale * cumulativeProbability);

        // STILL TO IMPLEMENT HERE: Handing carrying, rescaling and output bits here
    }

    return output;  // STILL TO IMPLEMNT: Output should be the binary representation of the encoded range - smalles number that falls into the final range
}

std::vector<char> LZMACompression::rangeDecode(std::vector<char> encodedDataStream) {
    std::vector<char> output;
    unsigned int low = 0;
    unsigned int range = static_cast<unsigned int>(-1);
    unsigned int code = 0;

    std::map<char, float> probabilities = calculateSymbolProbabilities(encodedDataStream);

    // Decode each symbol in the encodedDataStream
    for(size_t i = 0; i < encodedDataStream.size(); i++) {
        unsigned int scale = range;     // Calculate the total scale of the probabilities

        // Determine which range the code falls into:
        for(auto&p : probabilities) {
            unsigned int high = low + static_cast<unsigned int>(scale * p.second);

            if(code < high) {
                output.push_back(p.first);
                range - high - low;

                // Remove the contribution of all previous symbols from low
                float cumulativeProbability = 0;
                for(auto& prevP : probabilities) {
                    if(prevP.first == p.first)
                        break;
                    
                    cumulativeProbability += prevP.second;
                }

                low += static_cast<unsigned int>(scale * cumulativeProbability);
                break;
            }
        }

        // STILL TO IMPLEMENT HERE: Handing carrying, rescaling and output bits here
    }

    return output;
}

std::vector<char> LZMACompression::compress(std::vector<char> &inputData) {
    
}

std::vector<char> LZMACompression::decompress(std::vector<char> &compressedData) {
    
}

std::string LZMACompression::compress(std::string &inputData) {
    
}

std::string LZMACompression::decompress(std::string &compressedData) {
    
}