#include "LZMA-Compression.h"


void LZMACompression::initialiseDictionary(unsigned int size) {
    dictionarySize = size;
    dictionary.clear();
    dictionary.resize(size, 0);
}

std::pair<unsigned int, unsigned int> LZMACompression::findMatch(std::vector<char> sequence, unsigned int position) {
    unsigned int matchingDistance = 0;
    unsigned int matchingLength = 0;

    for(unsigned int i = 0; i < dictionary.size(); i++) {
        unsigned int length = 0;

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

std::pair<unsigned int, unsigned int> LZMACompression::encodeLength(unsigned int length) {
    return std::make_pair(length / 2, length % 2);  // Simple length encoding for now
}

unsigned int LZMACompression::decodeLength(std::pair<unsigned int, unsigned int> encodedLength) {
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
    for(unsigned int i = 0; i < encodedDataStream.size(); i++) {
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
    std::vector<char> output;

    for(unsigned int i = 0; i < inputData.size();) {
        std::pair<unsigned int, unsigned int> match = findMatch(inputData, i);   // Find the longest match in the dictionary - distance, length

        if(match.second > 0) {  // If a match is found, encode the distance and length
            output.push_back(static_cast<char>(match.first));
            output.push_back(static_cast<char>(match.second));

            i += match.second;  // Skip ahead by the length of the match

        } else {                // If no match is found, process the unmatched byte
            std::vector<char> unmatchedByte = processUnmatchedBytes({inputData[i]});
            output.insert(output.end(), unmatchedByte.begin(), unmatchedByte.end());

            i++;    // Move to the next byte
        }
    }

    output = rangeEncode(output);   // Perform range encoding on the output
    return output;
}

std::vector<char> LZMACompression::decompress(std::vector<char> &compressedData) {
    std::vector<char> output;

    std::vector<char> rangeDecodedData = rangeDecode(compressedData);   // Range Decode the data

    for(size_t i = 0; i < rangeDecodedData.size();) {
        if(i + 1 < rangeDecodedData.size() && rangeDecodedData[i] < dictionary.size() && rangeDecodedData[i + 1] > 0) {
            // Since current byte and next byte are interpreted as distance and length, add the corresponding data from the dictionary to the output
            unsigned int distance = rangeDecodedData[i];
            unsigned int length = rangeDecodedData[i + 1];

            for(int j = 0; j < length; j++)
                output.push_back(dictionary[distance]);

            i += 2;    // Move ahead by 2 bytes in the input

        } else {       // Otherwise, process the byte as unmatched
            std::vector<char> matchedByte = processUnmatchedBytes({rangeDecodedData[i]});
            output.insert(output.end(), matchedByte.begin(), matchedByte.end());

            i++;       // Move to the next byte
        }
    }

    return output;
}

std::string LZMACompression::compress(std::string &inputData) {
    std::vector<char> data(inputData.begin(), inputData.end());
    data = compress(data);

    std::string output(data.begin(), data.end());
    return output;
}

std::string LZMACompression::decompress(std::string &compressedData) {
    std::vector<char> data(compressedData.begin(), compressedData.end());
    data = decompress(data);

    std::string output(data.begin(), data.end());
    return output;
}