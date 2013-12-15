#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>
#include <iostream>
#include "lexer.hpp"
#include "token.hpp"
#include "ast.hpp"

class Parser {
public:
    Parser(std::string const &sourceFile)
    {
        lexer_.open(sourceFile);
        binaryOperationPrecedence_['='] = 50;
        binaryOperationPrecedence_['>'] = 100;
        binaryOperationPrecedence_['<'] = 100;
        binaryOperationPrecedence_['+'] = 200;
        binaryOperationPrecedence_['-'] = 200;
        binaryOperationPrecedence_['*'] = 400;
        binaryOperationPrecedence_['/'] = 400;
    }

    void Parse()
    {
        getNextToken();

        while (1) {
            TokenType type = currentToken_->GetType();
            AST::FunctionBody *f = NULL;
            switch (type) {
                case eof_:
                    return;
                //                case identifier_:
                //                    f = parseDefinition();
                //                    if (f)
                //                        std::cout << f << " 1" << std::endl;
                //                    else getNextToken();
                //                    break;
                default:
                    f = parseTopLevelExpression();
                    if (f)
                        f->Print();
                    else
                        getNextToken();
                    break;
            }
            // AST::Expression *ex = parseExpression();
            // if (ex) {
            //     ex->Print(0);
            //     printf("\n>> %d\n", ex->Process());
            //     printf("\n");
            // } else {
            //     getNextToken();
            // }
        }
    }

private:
    Lexer lexer_;
    Token *currentToken_;
    std::map<char, int> binaryOperationPrecedence_;

    void getNextToken()
    {
        currentToken_ = lexer_.GetNextToken();
    }

    int getTokenPrecedence()
    {
        if (currentToken_->GetType() != operator_)
            return -1;

        char operation = ((TokenXXX *)currentToken_)->GetID();

        int prec = binaryOperationPrecedence_[operation];
        if (prec <= 0)
            return -1;
        return prec;
    }

    AST::Expression *parseExpression();
    AST::Expression *parseNumberExpression();
    AST::Expression *parseParenthesesExpression();
    AST::Expression *parsePrimary();
    AST::Expression *parseBinOpRHS(int, AST::Expression *);
    AST::Expression *parseIdentifierExpression();

    AST::FunctionPrototype *parsePrototype();
    AST::FunctionBody *parseDefinition();
    AST::FunctionBody *parseTopLevelExpression();
};

#endif /* end of include guard: PARSER_HPP */
