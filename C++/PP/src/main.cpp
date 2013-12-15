#include <iostream>
#include <string>

#include "parser.hpp"

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: XXX <source filename>" << std::endl;
        return 1;
    }
    std::string sourceFile = argv[1];

    Parser p(sourceFile);
    
    p.Parse();

    // Lexer p;
    // p.open(sourceFile);
    // 
    // Token *t = p.GetNextToken();
    // do {
    //     t->PrintInfo();
    //     t = p.GetNextToken();
    // } while (t->GetType() != eof_);
    return 0;
}
