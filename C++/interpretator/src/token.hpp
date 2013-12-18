#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <iostream>

struct Token {
    enum Type {
        tt_opening_bracket, // (
        tt_closing_bracket, // )
        tt_comma,           // ,
        tt_colon,           // :
        tt_identifier,      // variable or function name
        tt_operation,       // + - * / =
        tt_number,          // 312
        tt_def,             // keyword def
        tt_end,             // keyword end
        tt_while,           // keyword while
        tt_if,              // keyword if
        tt_return,          // keyword return
        tt_print,           // keyword print
        tt_read,            // keyword read
        tt_unknown          //
    };

    Token(Token const &other) : type(other.type), name(other.name), lineNumber(other.lineNumber)
    {
    }

    Token(Type type_, std::string const &name_, int lineNumber_)
        : type(type_), name(name_), lineNumber(lineNumber_)
    {
    }

    void debug() const
    {
        std::string t;
        switch (type) {
            case tt_opening_bracket:
                t = "tt_opening_bracket";
                break;
            case tt_closing_bracket:
                t = "tt_closing_bracket";
                break;
            case tt_comma:
                t = "tt_comma";
                break;
            case tt_colon:
                t = "tt_colon";
                break;
            case tt_identifier:
                t = "tt_identifier";
                break;
            case tt_operation:
                t = "tt_operation";
                break;
            case tt_number:
                t = "tt_number";
                break;
            case tt_def:
                t = "tt_def";
                break;
            case tt_end:
                t = "tt_end";
                break;
            case tt_while:
                t = "tt_while";
                break;
            case tt_if:
                t = "tt_if";
                break;
            case tt_return:
                t = "tt_return";
                break;
            case tt_print:
                t = "tt_print";
                break;
            case tt_read:
                t = "tt_read";
                break;
            default:
                break;
        }
        std::cout << "Type: " << t << " Name: <" << name << "> At line #" << lineNumber
                  << std::endl;
    }

    Type type;
    std::string name;
    int lineNumber;
};

#endif /* end of include guard: TOKEN_HPP */
