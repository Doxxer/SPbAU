#include "parser.hpp"

AST::Expression *Parser::parseNumberExpression()
{
    AST::Expression *result = new AST::Number(((TokenNumber *)currentToken_)->GetValue());
    getNextToken(); // получаем число
    return result;
}

AST::Expression *Parser::parseParenthesesExpression()
{
    getNextToken();
    AST::Expression *v = parseExpression();
    if (!v)
        return 0;

    if (((TokenXXX *)currentToken_)->GetID() != ')') {
        return AST::Error("expected ')'");
    }
    getNextToken();
    return v;
}

AST::Expression *Parser::parseExpression()
{
    AST::Expression *lhs = parsePrimary();
    if (!lhs)
        return 0;
    return parseBinOpRHS(0, lhs);
}

AST::Expression *Parser::parseBinOpRHS(int expressionPrecedence, AST::Expression *lhs)
{
    while (1) {
        int tokPrec = getTokenPrecedence();

        if (tokPrec < expressionPrecedence)
            return lhs;

        char BinOp = ((TokenXXX *)currentToken_)->GetID();
        getNextToken();

        AST::Expression *rhs = parsePrimary();
        if (!rhs)
            return 0;

        int nextPrecedence = getTokenPrecedence();
        if (tokPrec < nextPrecedence) {
            rhs = parseBinOpRHS(tokPrec + 1, rhs);
            if (rhs == 0)
                return 0;
        }

        lhs = new AST::BinaryExpression(BinOp, lhs, rhs);
    }
}

AST::Expression *Parser::parsePrimary()
{
    TokenType type = currentToken_->GetType();
    switch (type) {
        default:
            return AST::Error("unknown token when expecting an expression\n");
        case identifier_:
            return parseIdentifierExpression();
        case number_:
            return parseNumberExpression();
        case operator_:
            if (((TokenXXX *)currentToken_)->GetID() == '(') {
                return parseParenthesesExpression();
            } else {
                return AST::Error("unknown token when expecting an expression\n");
            }
    }
}

AST::Expression *Parser::parseIdentifierExpression()
{
    TokenIdentifier *token = (TokenIdentifier *)currentToken_;
    std::string IdName = token->GetIdentifier();

    getNextToken(); // получаем идентификатор.

    if (((TokenXXX *)currentToken_)->GetID() != '(') // Ссылка на переменную.
        return new AST::Variable(IdName);

    // Вызов функции.
    getNextToken(); // получаем (
    std::vector<AST::Expression *> args;
    if (((TokenXXX *)currentToken_)->GetID() != ')') {
        while (1) {
            AST::Expression *arg = parseExpression();
            if (!arg)
                return 0;
            args.push_back(arg);

            if (((TokenXXX *)currentToken_)->GetID() == ')')
                break;

            if (((TokenXXX *)currentToken_)->GetID() != ',')
                return AST::Error("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }
    getNextToken();

    return new AST::Call(IdName, args);
}

AST::FunctionPrototype *Parser::parsePrototype()
{
    if (currentToken_->GetType() != identifier_)
        return AST::ErrorPrototype("Expected function name in prototype");

    std::string FnName = ((TokenIdentifier *)currentToken_)->GetIdentifier();
    getNextToken();

    if (((TokenXXX *)currentToken_)->GetID() != '(')
        return AST::ErrorPrototype("Expected '(' in prototype");

    // Считываем список наименований аргументов.
    std::vector<std::string> ArgNames;
    getNextToken();
    while (currentToken_->GetType() == identifier_) {
        ArgNames.push_back(((TokenIdentifier *)currentToken_)->GetIdentifier());
        getNextToken();
    }

    if (((TokenXXX *)currentToken_)->GetID() != ')')
        return AST::ErrorPrototype("Expected ')' in prototype");

    getNextToken(); // get ')'

    return new AST::FunctionPrototype(FnName, ArgNames);
}

AST::FunctionBody *Parser::parseDefinition()
{
    getNextToken(); // get 'def'
    AST::FunctionPrototype *prototype = parsePrototype();
    if (!prototype)
        return 0;

    if (AST::Expression *body = parseExpression())
        return new AST::FunctionBody(prototype, body);
    return 0;
}

AST::FunctionBody *Parser::parseTopLevelExpression()
{
    if (AST::Expression *body = parseExpression()) {
        AST::FunctionPrototype *prototype =
            new AST::FunctionPrototype("", std::vector<std::string>());
        return new AST::FunctionBody(prototype, body);
    }
    return 0;
}
