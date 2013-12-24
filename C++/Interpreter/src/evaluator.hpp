#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <cstddef>
#include <string>
#include <map>
#include <stack>
#include "ast.hpp"
#include "visitor.hpp"
#include "parser.hpp"
#include "interpreter_error.hpp"

class FunctionReturn {
public:
    explicit FunctionReturn(int value) : value_(value)
    {
    }
    int Value() const
    {
        return value_;
    }
    ;

private:
    int value_;
};

class RuntimeError : public InterpreterError {
public:
    explicit RuntimeError(size_t line, std::string const &message = "")
        : InterpreterError(line, message)
    {
    }
};

class UndefinedVariableError : public RuntimeError {
public:
    explicit UndefinedVariableError(size_t line, std::string const &name)
        : RuntimeError(line, "undefined variable " + name)
    {
    }
};

class UndefinedFunctionError : public RuntimeError {
public:
    explicit UndefinedFunctionError(size_t line, std::string const &name)
        : RuntimeError(line, "undefined function " + name)
    {
    }
};

class ArgumentsNumberMismatchError : public RuntimeError {
public:
    explicit ArgumentsNumberMismatchError(size_t line, std::string const &name)
        : RuntimeError(line, "arguments number mismatch for " + name)
    {
    }
};

class DivizionByZeroError : public RuntimeError {
public:
    explicit DivizionByZeroError(size_t line) : RuntimeError(line, "divizion by zero")
    {
    }
};

class Evaluator : public Visitor {
public:
    explicit Evaluator(Program const &program)
        : entryPoint_(program.EntryPoint), functions_(program.Functions)
    {
    }

    void eval()
    {
        entryPoint_->accept(*this);
    }

    int visit(AST::FunctionDefinition const &);
    int visit(AST::VariableDefinition const &);
    int visit(AST::Number const &);
    int visit(AST::Variable const &);
    int visit(AST::Call const &);
    int visit(AST::BinaryExpression const &);
    int visit(AST::Read const &);
    int visit(AST::Print const &);
    int visit(AST::Condition const &);
    int visit(AST::If const &);
    int visit(AST::While const &);
    int visit(AST::Return const &);

private:
    ExpressionPtr entryPoint_;
    std::map<std::string, FunctionPtr> functions_;
    std::map<std::string, int> global_variables_;
    std::stack<std::map<std::string, int> > locale_variables_;

    bool get_variable_value(std::string const &name, int &value)
    {
        if (!locale_variables_.empty()) {
            std::map<std::string, int> const & locals = locale_variables_.top();
            std::map<std::string, int>::const_iterator var = locals.find(name);
            if (var != locals.end()) {
                value = var->second;
                return true;
            }
        }

        std::map<std::string, int>::const_iterator var = global_variables_.find(name);
        if (var != global_variables_.end()) {
            value = var->second;
            return true;
        }
        return false;
    }

    void set_variable_value(std::string const &name, int value)
    {
        if (!locale_variables_.empty())
            locale_variables_.top()[name] = value;
        else
            global_variables_[name] = value;
    }

    Evaluator(Evaluator const &);
    Evaluator &operator=(Evaluator const &);
};

#endif /* end of include guard: EVALUATOR_HPP */
