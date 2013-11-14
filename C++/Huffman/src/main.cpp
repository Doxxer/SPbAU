#include <iostream>
#include <string>
#include "huffmanDecode.hpp"
#include "huffmanEncode.hpp"

int main(int argc, char const *argv[])
{
    std::string inputFile = "";
    std::string outputFile = "";
    int compressFlag = -1;
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == std::string("-c")) {
            compressFlag = 1;
            continue;
        }
        if (argv[i] == std::string("-d")) {
            compressFlag = 0;
            continue;
        }
        if (argv[i] == std::string("-i") && i + 1 < argc) {
            inputFile = argv[++i];
            continue;
        }
        if (argv[i] == std::string("-o") && i + 1 < argc) {
            outputFile = argv[++i];
            continue;
        }
    }

    if (compressFlag == -1 || inputFile.empty() || outputFile.empty()) {
        std::cout << "Usage: arj [-c|-d] -i <input filename> -o <output filename>" << std::endl;
        return 1;
    }

    if (compressFlag)
        Compress(inputFile, outputFile);
    else
        Decompress(inputFile, outputFile);
    return 0;
}
