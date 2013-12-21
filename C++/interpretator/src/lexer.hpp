#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "token.hpp"

class Lexer {
public:
    Lexer(std::string const &sourceFileName);

    Token const *peek()
    {
        return position_ != content_.end() ? &*position_ : 0;
    }

    Token const *peek_next()
    {
        return position_ + 1 != content_.end() ? &*(position_ + 1) : 0;
    }

    Token const *get()
    {
        return position_ != content_.end() ? &*position_++ : 0;
    }

private:
    Lexer &operator=(Lexer const &);
    Lexer(Lexer const &other);

    void processLine(std::string const &, size_t);

    void getOperator(std::string::const_iterator &, Token &);
    void getIdentifier(std::string::const_iterator &, Token &);
    void getNumber(std::string::const_iterator &, Token &);

    std::vector<Token> content_;
    std::vector<Token>::iterator position_;
};

#endif /* end of include guard: LEXER_HPP */
