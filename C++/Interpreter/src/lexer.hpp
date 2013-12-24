#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <fstream>
#include "token.hpp"
#include "interpreter_error.hpp"

class LexerError : public InterpreterError {
public:
    explicit LexerError(size_t line, std::string const &message) : InterpreterError(line, message)
    {
    }
};

class Lexer {
public:
    Lexer(std::string const &sourceFileName);

    Token const &peek(size_t offset = 0)
    {
        return (position_ + offset) != content_.end() ? *(position_ + offset) : Token::EOFToken;
    }
    
    Token const &get()
    {
        return position_ != content_.end() ? *position_++ : Token::EOFToken;
    }

private:
    Lexer &operator=(Lexer const &);
    Lexer(Lexer const &other);

    void processLine(std::string const &, size_t);

    void getOperator(std::string::const_iterator &, Token &);
    void getIdentifier(std::string::const_iterator &, Token &);
    void getNumber(std::string::const_iterator &, Token &);

    std::vector<Token> content_;
    std::vector<Token>::const_iterator position_;
};

#endif /* end of include guard: LEXER_HPP */
