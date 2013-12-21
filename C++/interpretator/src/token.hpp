#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstddef>
#include <string>
#include <iostream>

struct Token {
    enum Type {
        tt_opening_bracket, // (
        tt_closing_bracket, // )
        tt_comma,           // ,
        tt_colon,           // :
        tt_identifier,      // variable or function name
        tt_operation_plus,  //
        tt_operation_minus, //
        tt_operation_mult,  //
        tt_operation_div,   //
        tt_operation_eq,    //
        tt_inequality,      // > < >= <= == !=
        tt_number,          //
        tt_def,             // keyword def
        tt_end,             // keyword end
        tt_while,           // keyword while
        tt_if,              // keyword if
        tt_return,          // keyword return
        tt_print,           // keyword print
        tt_read,            // keyword read
        tt_cr,              // \n
        tt_eof,             // eof
        tt_unknown          //
    };

    Token(Type type_ = Token::tt_unknown, std::string const &name_ = "", size_t lineNumber_ = 0)
        : type(type_), name(name_), lineNumber(lineNumber_)
    {
    }

    Token(Token const &other) : type(other.type), name(other.name), lineNumber(other.lineNumber)
    {
    }

    void swap(Token &other)
    {
        std::swap(other.type, type);
        std::swap(other.name, name);
        std::swap(other.lineNumber, lineNumber);
    }
    Token &operator=(Token const &other)
    {
        if (this != &other)
            Token(other).swap(*this);
        return *this;
    }

    Type type;
    std::string name;
    size_t lineNumber;
};
#endif /* end of include guard: TOKEN_HPP */
