#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "token.hpp"

class Lexer {
public:
    Lexer(std::string const &sourceFileName);

    bool IsOk() const
    {
        return state_;
    }

    Token const *get()
    {
        return position_ != content_.end() ? &*position_++ : 0;
    }

private:
private:
    Lexer(Lexer const &);
    Lexer &operator=(Lexer const &);

    bool processLine(std::string &, int);

    std::vector<Token> content_;
    std::vector<Token>::iterator position_;
    bool state_;
};

#endif /* end of include guard: LEXER_HPP */
