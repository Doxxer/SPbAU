#include <cstdlib>
#include <map>
#include "parser.hpp"
#include "errors.hpp"

Program Parser::parse()
{
    ExpressionPtrs content;
    std::map<std::string, FunctionPtr> functions;

    while (lexer_.peek()->type != Token::tt_eof) {
        ExpressionPtr instrunction = parse_instruction();
        if (instrunction) {
            content.push_back(instrunction);
            continue;
        }

        FunctionPtr function = parse_function_defenition();
        if (function) {
            functions[function->Name()] = function;
            continue;
        }

        if (lexer_.peek()->type != Token::tt_eof)
            throw ParserError(lexer_.peek()->lineNumber);
    }

    return Program(ExpressionPtr(new AST::Program(content)), functions);
}

ExpressionPtr Parser::parse_instruction()
{
    while (lexer_.peek()->type == Token::tt_cr)
        lexer_.get();

    ExpressionPtr result = parse_read();
    if (!result)
        result = parse_print();
    if (!result)
        result = parse_variable_definition();
    if (!result)
        result = parse_expression();
    if (!result)
        result = parse_if();
    if (!result)
        result = parse_while();
    if (!result)
        result = parse_return();

    if (result) {
        while (lexer_.peek()->type == Token::tt_cr)
            lexer_.get();
    }

    return result;
}

ExpressionPtr Parser::parse_number()
{
    if (lexer_.peek()->type != Token::tt_number)
        return ExpressionPtr();

    Token const *t = lexer_.get();
    return ExpressionPtr(new AST::Number(atoi(t->name.c_str()), t->lineNumber));
}

ExpressionPtr Parser::parse_read()
{
    if (lexer_.peek()->type != Token::tt_read)
        return ExpressionPtr();
    lexer_.get(); // get read keyword

    Token const *t = lexer_.get();

    if (t->type != Token::tt_identifier)
        throw ParserError(t->lineNumber, "identifier expected");

    return ExpressionPtr(new AST::Read(t->name, t->lineNumber));
}

ExpressionPtr Parser::parse_print()
{
    if (lexer_.peek()->type != Token::tt_print)
        return ExpressionPtr();
    lexer_.get(); // get print keyword

    ExpressionPtr expr = parse_expression();
    if (!expr)
        throw ParserError(lexer_.peek()->lineNumber);

    return ExpressionPtr(new AST::Print(expr, lexer_.peek()->lineNumber));
}

ExpressionPtr Parser::parse_expression()
{
    ExpressionPtr lhs = parse_primary();
    if (!lhs)
        return ExpressionPtr();

    if (lexer_.peek()->type != Token::tt_operation_plus &&
        lexer_.peek()->type != Token::tt_operation_minus)
        return lhs;

    Token::Type operation = lexer_.get()->type;
    ExpressionPtr rhs = parse_expression();
    if (!rhs)
        throw ParserError(lexer_.peek()->lineNumber);

    char op;
    switch (operation) {
        case Token::tt_operation_plus:
            op = '+';
            break;
        case Token::tt_operation_minus:
            op = '-';
            break;
        default:
            throw ParserError(lexer_.peek()->lineNumber);
    }

    return ExpressionPtr(new AST::BinaryExpression(op, lhs, rhs, lexer_.peek()->lineNumber));
}

ExpressionPtr Parser::parse_primary()
{
    ExpressionPtr lhs = parse_value();
    if (!lhs)
        return ExpressionPtr();

    if (lexer_.peek()->type != Token::tt_operation_div &&
        lexer_.peek()->type != Token::tt_operation_mult)
        return lhs;

    Token::Type operation = lexer_.get()->type;

    ExpressionPtr rhs = parse_primary();
    if (!rhs)
        throw ParserError(lexer_.peek()->lineNumber);

    char op;
    switch (operation) {
        case Token::tt_operation_mult:
            op = '*';
            break;
        case Token::tt_operation_div:
            op = '/';
            break;
        default:
            throw ParserError(lexer_.peek()->lineNumber);
    }

    return ExpressionPtr(new AST::BinaryExpression(op, lhs, rhs, lexer_.peek()->lineNumber));
}

ExpressionPtr Parser::parse_value()
{
    // parse unary minus
    if (lexer_.peek()->type == Token::tt_operation_minus) {
        lexer_.get(); // get unary minus
        ExpressionPtr value = parse_value();
        if (!value)
            throw ParserError(lexer_.peek()->lineNumber);
        ExpressionPtr zero(new AST::Number(0, 0));
        return ExpressionPtr(
            new AST::BinaryExpression('-', zero, value, lexer_.peek()->lineNumber));
    }

    // not? parse (...)
    if (lexer_.peek()->type == Token::tt_opening_bracket) {
        lexer_.get(); // get (
        ExpressionPtr expr = parse_expression();
        if (!expr || lexer_.get()->type != Token::tt_closing_bracket)
            throw ParserError(lexer_.peek()->lineNumber);
        return expr;
    }

    ExpressionPtr value = parse_number();
    if (!value)
        value = parse_identifier();
    return value;
}

ExpressionPtr Parser::parse_identifier()
{
    if (lexer_.peek()->type != Token::tt_identifier)
        return ExpressionPtr();
    std::string name = lexer_.get()->name;

    // parse variable
    if (lexer_.peek()->type != Token::tt_opening_bracket)
        return ExpressionPtr(new AST::Variable(name, lexer_.peek()->lineNumber));

    // parse function call
    lexer_.get(); // get (
    ExpressionPtrs params;

    if (lexer_.peek()->type != Token::tt_closing_bracket) {
        // collect params
        while (true) {
            ExpressionPtr param = parse_expression();
            if (!param)
                throw ParserError(lexer_.peek()->lineNumber);
            params.push_back(param);

            // if , then continue
            if (lexer_.peek()->type == Token::tt_comma)
                lexer_.get();
            else
                break;
        }
        if (lexer_.peek()->type != Token::tt_closing_bracket)
            throw ParserError(lexer_.peek()->lineNumber);
    }
    return ExpressionPtr(new AST::Call(name, params, lexer_.get()->lineNumber));
}

ExpressionPtr Parser::parse_variable_definition()
{
    // is it a=2 or a(2) ?
    if (lexer_.peek()->type != Token::tt_identifier ||
        lexer_.peek_next()->type == Token::tt_opening_bracket)
        return ExpressionPtr();

    std::string name = lexer_.get()->name;

    if (lexer_.get()->type != Token::tt_operation_eq)
        throw ParserError(lexer_.peek()->lineNumber);

    ExpressionPtr expression = parse_expression();
    if (!expression)
        throw ParserError(lexer_.peek()->lineNumber);

    return ExpressionPtr(new AST::VariableDefinition(name, expression, lexer_.peek()->lineNumber));
}

ExpressionPtr Parser::parse_condition()
{
    ExpressionPtr left = parse_expression();
    if (!left)
        return ExpressionPtr();

    Token const *comp_token = lexer_.get(); // get compare operator
    if (comp_token->type != Token::tt_inequality)
        throw ParserError(comp_token->lineNumber);

    ExpressionPtr right = parse_expression();
    if (!right)
        throw ParserError(comp_token->lineNumber);

    return ExpressionPtr(new AST::Condition(comp_token->name, left, right, comp_token->lineNumber));
}

ExpressionPtr Parser::parse_if()
{
    if (lexer_.peek()->type != Token::tt_if)
        return ExpressionPtr();
    lexer_.get(); // get if

    ExpressionPtr condition = parse_condition();
    if (!condition || lexer_.get()->type != Token::tt_colon || lexer_.get()->type != Token::tt_cr)
        throw ParserError(lexer_.peek()->lineNumber);

    ExpressionPtrs content;
    while (lexer_.peek()->type != Token::tt_end) {
        ExpressionPtr instruction = parse_instruction();
        if (!instruction)
            throw ParserError(lexer_.peek()->lineNumber);
        content.push_back(instruction);
    }
    lexer_.get(); // get end

    return ExpressionPtr(new AST::If(condition, content));
}

ExpressionPtr Parser::parse_while()
{
    if (lexer_.peek()->type != Token::tt_while)
        return ExpressionPtr();
    lexer_.get(); // get while

    ExpressionPtr condition = parse_condition();
    if (!condition || lexer_.get()->type != Token::tt_colon || lexer_.get()->type != Token::tt_cr)
        throw ParserError(lexer_.peek()->lineNumber);

    ExpressionPtrs content;
    while (lexer_.peek()->type != Token::tt_end) {
        ExpressionPtr instruction = parse_instruction();
        if (!instruction)
            throw ParserError(lexer_.peek()->lineNumber);
        content.push_back(instruction);
    }
    lexer_.get(); // get end

    return ExpressionPtr(new AST::While(condition, content));
}

ExpressionPtr Parser::parse_return()
{
    if (lexer_.peek()->type != Token::tt_return)
        return ExpressionPtr();
    lexer_.get(); // get return

    ExpressionPtr expression = parse_expression();
    if (!expression)
        throw ParserError(lexer_.peek()->lineNumber);
    return ExpressionPtr(new AST::Return(expression, lexer_.peek()->lineNumber));
}

FunctionPtr Parser::parse_function_defenition()
{
    if (lexer_.peek()->type != Token::tt_def)
        return FunctionPtr();
    lexer_.get(); // get def

    Token const *token_function_name = lexer_.get();
    if (token_function_name->type != Token::tt_identifier ||
        lexer_.get()->type != Token::tt_opening_bracket)
        throw ParserError(lexer_.peek()->lineNumber);

    std::vector<std::string> params;
    if (lexer_.peek()->type != Token::tt_closing_bracket) {

        // collect param
        while (true) {
            Token const *param = lexer_.get();
            if (param->type != Token::tt_identifier)
                throw ParserError(lexer_.peek()->lineNumber);
            params.push_back(param->name);

            // if , then continue
            if (lexer_.peek()->type == Token::tt_comma)
                lexer_.get(); // get ,
            else
                break;
        }
        if (lexer_.peek()->type != Token::tt_closing_bracket)
            throw ParserError(lexer_.peek()->lineNumber);
    }
    lexer_.get(); // get)

    if (lexer_.get()->type != Token::tt_colon || lexer_.get()->type != Token::tt_cr)
        throw ParserError(lexer_.peek()->lineNumber);

    ExpressionPtrs content;
    while (lexer_.peek()->type != Token::tt_end) {
        ExpressionPtr instruction = parse_instruction();
        if (!instruction)
            throw ParserError(lexer_.peek()->lineNumber);
        content.push_back(instruction);
    }
    lexer_.get(); // get end

    if (lexer_.get()->type != Token::tt_cr)
        throw ParserError(lexer_.peek()->lineNumber);

    return FunctionPtr(new AST::FunctionDefinition(token_function_name->name, params, content));
}
