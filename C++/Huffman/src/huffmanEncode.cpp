#include "EncodeUtilities.hpp"
#include "huffmanEncode.hpp"
#include "BitFile.hpp"
#include <cstddef>
#include <climits>
#include <cstdio>

std::vector<size_t> readFrequencies(std::string const &inputFileName)
{
    std::ifstream inputFile(inputFileName.c_str(), std::ifstream::binary | std::ifstream::in);
    std::vector<size_t> frequencies((size_t)1 << CHAR_BIT * sizeof(unsigned char), 0);

    char byte;
    while (inputFile.get(byte)) {
        frequencies[(unsigned char)byte]++;                        
    }
    return frequencies;
}

void encode(std::string const &inputFileName,
            std::string const &outputFileName,
            std::vector<int> const &codes,
            std::vector<int> const &lengths,
            std::vector<size_t> const &frequencies)
{
    std::ifstream inputFile(inputFileName.c_str(),
                            std::ifstream::binary | std::ifstream::in | std::ifstream::ate);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, inputFile.beg);

    BitFile outputFile(outputFileName, BitFile::Write);
    outputFile.write(fileSize);
    outputFile.write(frequencies.size());
    for (size_t i = 0; i < frequencies.size(); ++i) {
        outputFile.write(frequencies[i]);
    }

    char byte;
    while (inputFile.get(byte)) {
        unsigned char c = (unsigned char)byte;
        int code = codes[c];
        for (int k = lengths[c] - 1; k >= 0; --k) {
            outputFile.writeBit(code & (1 << k));
        }
    }
}

void Compress(std::string const &inputFileName, std::string const &outputFileName)
{
    EncodeUtilities helper(readFrequencies(inputFileName));
    encode(inputFileName,
           outputFileName,
           helper.GetCodes(),
           helper.GetCodeLengths(),
           helper.GetFrequencies());
}
