#include "EncodeUtilities.hpp"
#include "huffmanDecode.hpp"
#include "BitFile.hpp"

void decode(BitFile &inputFile,
            std::string const &outputFileName,
            size_t sourceFileSize,
            std::vector<int> const &numberInternals,
            std::vector<std::pair<int, int> > const &sorted_symbols,
            std::vector<int> const &offset)
{
    std::ofstream outputFile(outputFileName.c_str(), std::ofstream::out | std::ofstream::trunc);

    for (size_t i = 0; i < sourceFileSize; ++i) {
        int code = inputFile.readBit();
        int length = 1;
        while (code < numberInternals[length]) {
            code <<= 1;
            code += inputFile.readBit();
            length++;
        }
        outputFile << (unsigned char)(sorted_symbols
                                          [offset[length] + code - numberInternals[length]].first);
    }
}

void Decompress(std::string const &inputFileName, std::string const &outputFileName)
{
    BitFile inputFile(inputFileName, BitFile::Read);

    size_t sourceFileSize, dictionary_size;
    inputFile.read(sourceFileSize);
    inputFile.read(dictionary_size);

    std::vector<size_t> frequencies(dictionary_size, 0);
    for (size_t i = 0; i < dictionary_size; ++i) {
        inputFile.read(frequencies[i]);
    }

    EncodeUtilities utilities(frequencies);

    decode(inputFile,
           outputFileName,
           sourceFileSize,
           utilities.GetNumberInternals(),
           utilities.GetSortedSymbols(),
           utilities.GetOffset());
}
