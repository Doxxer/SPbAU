#include "lexer.hpp"
#include <cassert>

Lexer::Lexer() : lastToken_(NULL), lastChar_(' ')
{
}

void Lexer::open(std::string const &sourceFileName)
{
    inputFile_.open(sourceFileName, std::ifstream::in);
}

Lexer::~Lexer()
{
    inputFile_.close();
}

void Lexer::getNextToken()
{
    // skip spaces
    while (isspace(lastChar_))
        lastChar_ = inputFile_.get();

    // identifier
    if (isalpha(lastChar_) || lastChar_ == '_') {
        std::string idstr(1, lastChar_);
        lastChar_ = inputFile_.get();

        while (isalnum(lastChar_) || lastChar_ == '_') {
            idstr += lastChar_;
            lastChar_ = inputFile_.get();
        }
        
        lastToken_ = new TokenIdentifier(idstr);
        return;
    }

    // number
    if (isdigit(lastChar_)) {
        std::string NumStr;
        do {
            NumStr += lastChar_;
            lastChar_ = inputFile_.get();
        } while (isdigit(lastChar_));

        lastToken_ = new TokenNumber(atoi(NumStr.c_str()));
        return;
    }

    // comment
    if (lastChar_ == '#') {
        do {
            lastChar_ = inputFile_.get();
        } while (lastChar_ != EOF && lastChar_ != '\n' && lastChar_ != '\r');

        if (lastChar_ != EOF) {
            getNextToken();
            return;
        }
    }

    // EOF
    if (lastChar_ == EOF) {
        lastToken_ = new TokenEOF();
        return;
    }

    // other symbol (+, -, =, /, *, (, ), s)
    char t = lastChar_;
    lastChar_ = inputFile_.get();
    lastToken_ = new TokenXXX(t);
}
