#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <string>
#include "token.hpp"

class Lexer {
public:
    Lexer();
    ~Lexer();

    void open(std::string const &sourceFileName);

    Token *GetNextToken()
    {
        delete lastToken_;
        lastToken_ = NULL;
        getNextToken();
        return lastToken_;
    }

private:
    Lexer(Lexer const &);
    Lexer &operator=(Lexer const &);

    void getNextToken();

    std::ifstream inputFile_;
    Token *lastToken_;
    char lastChar_;
};

#endif /* end of include guard: LEXER_HPP */
