#include "evaluator.hpp"
#include "errors.hpp"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int Evaluator::visit(AST::Program const &a)
{
    for (std::vector<ExpressionPtr>::const_iterator it = a.content().begin();
         it != a.content().end();
         ++it) {
        try
        {
            (*it)->accept(*this);
        }
        catch (FunctionReturn const &r)
        {
            return r.Value();
        }
    }
    return 0;
}

int Evaluator::visit(AST::FunctionDefinition const &a)
{
    for (std::vector<ExpressionPtr>::const_iterator it = a.content().begin();
         it != a.content().end();
         ++it) {
        try
        {
            (*it)->accept(*this);
        }
        catch (FunctionReturn const &r)
        {
            return r.Value();
        }
    }
    return 0;
}

int Evaluator::visit(AST::Number const &a)
{
    return a.Value();
}

int Evaluator::visit(AST::Variable const &a)
{
    int value = 0;
    if (!get_variable_value(a.Name(), value))
        throw UndefinedVariableError(a.LineNumber(), a.Name());
    return value;
}

int Evaluator::visit(AST::Read const &a)
{
    int n;
    cin >> n;
    set_variable_value(a.Variable(), n);
    return n;
}

int Evaluator::visit(AST::VariableDefinition const &a)
{
    int n = a.Expr()->accept(*this);
    set_variable_value(a.Name(), n);
    return n;
}

int Evaluator::visit(AST::Print const &a)
{
    int n = a.Expr()->accept(*this);
    cout << n << endl;
    return n;
}

int Evaluator::visit(AST::Return const &a)
{
    int n = a.Expr()->accept(*this);
    throw FunctionReturn(n);
}

int Evaluator::visit(AST::If const &a)
{

    int value = a.Condition()->accept(*this);
    if (value) {
        for (std::vector<ExpressionPtr>::const_iterator it = a.content().begin();
             it != a.content().end();
             ++it)
            value = (*it)->accept(*this);
    }
    return value;
}

int Evaluator::visit(AST::While const &a)
{
    int condition = a.Condition()->accept(*this);
    int value = 0;
    while (condition) {
        for (std::vector<ExpressionPtr>::const_iterator it = a.content().begin();
             it != a.content().end();
             ++it)
            value = (*it)->accept(*this);
        condition = a.Condition()->accept(*this);
    }
    return value;
}

int Evaluator::visit(AST::Call const &a)
{
    std::map<std::string, FunctionPtr>::iterator it = functions_.find(a.Name());
    if (it == functions_.end())
        throw UndefinedFunctionError(a.LineNumber(), a.Name());

    FunctionPtr func = it->second;
    ExpressionPtrs args = a.Params();
    std::vector<std::string> params = func->Params();

    if (params.size() != args.size())
        throw ArgumentsNumberMismatchError(a.LineNumber(), a.Name());

    std::map<std::string, int> function_locals;
    for (size_t i = 0; i < args.size(); ++i) {
        int value = (args[i])->accept(*this);
        function_locals[params[i]] = value;
    }

    locale_variables_.push(function_locals);

    // run function
    int res = func->accept(*this);
    locale_variables_.pop();
    return res;
}

int Evaluator::visit(AST::BinaryExpression const &a)
{
    int lhs = a.Left()->accept(*this);
    int rhs = a.Right()->accept(*this);

    switch (a.Operation()) {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            if (rhs == 0)
                throw DivizionByZeroError(a.LineNumber());
            return lhs / rhs;
    }

    return 0;
}

int Evaluator::visit(AST::Condition const &a)
{
    int lhs = a.Left()->accept(*this);
    int rhs = a.Right()->accept(*this);

    if (a.Operation() == "<")
        return lhs < rhs;
    if (a.Operation() == "<=")
        return lhs <= rhs;
    if (a.Operation() == ">")
        return lhs > rhs;
    if (a.Operation() == ">=")
        return lhs >= rhs;
    if (a.Operation() == "==")
        return lhs == rhs;
    if (a.Operation() == "!=")
        return lhs != rhs;
    return 0;
}
