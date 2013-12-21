#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "ast_definition.hpp"

class Visitor {
public:
    virtual int visit(AST::Program const &) = 0;

    virtual int visit(AST::FunctionDefinition const &) = 0;
    virtual int visit(AST::VariableDefinition const &) = 0;

    virtual int visit(AST::Number const &) = 0;
    virtual int visit(AST::Variable const &) = 0;
    virtual int visit(AST::Call const &) = 0;
    virtual int visit(AST::BinaryExpression const &) = 0;
    virtual int visit(AST::Read const &) = 0;
    virtual int visit(AST::Print const &) = 0;

    virtual int visit(AST::Condition const &) = 0;
    virtual int visit(AST::If const &) = 0;
    virtual int visit(AST::While const &) = 0;
    virtual int visit(AST::Return const &) = 0;
};

#endif /* end of include guard */
