#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>
#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"
#include "interpreter_error.hpp"

class ParserError : public InterpreterError {
public:
    explicit ParserError(size_t line, std::string const &message = "")
        : InterpreterError(line, message)
    {
    }
};

struct Program {

    Program(ExpressionPtr const &ep, std::map<std::string, FunctionPtr> const &funcs)
        : EntryPoint(ep), Functions(funcs)
    {
    }

    ExpressionPtr EntryPoint;
    std::map<std::string, FunctionPtr> Functions;
};

class Parser {
public:
    Parser(std::string const &sourceFile) : lexer_(sourceFile)
    {
    }

    Program parse();

private:
    Lexer lexer_;

    Parser(Parser const &);
    Parser &operator=(Parser const &);

    ExpressionPtr parse_instruction();
    FunctionPtr parse_function_defenition();
    ExpressionPtr parse_primary();
    ExpressionPtr parse_value();
    ExpressionPtr parse_identifier();
    ExpressionPtr parse_number();
    ExpressionPtr parse_read();
    ExpressionPtr parse_print();
    ExpressionPtr parse_variable_definition();
    ExpressionPtr parse_expression();
    ExpressionPtr parse_condition();
    ExpressionPtr parse_if();
    ExpressionPtr parse_while();
    ExpressionPtr parse_return();
};

#endif /* end of include guard: PARSER_HPP */
