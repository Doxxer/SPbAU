#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <memory>
#include <cstddef>
#include "visitor.hpp"
#include "ast_definition.hpp"

typedef std::shared_ptr<AST::Expression> ExpressionPtr;
typedef std::shared_ptr<AST::FunctionDefinition> FunctionPtr;
typedef std::vector<ExpressionPtr> ExpressionPtrs;

namespace AST {
    
    class Expression {
    public:
        Expression(size_t lineNumber) : lineNumber_(lineNumber)
        {
        }
        
        size_t LineNumber() const
        {
        return lineNumber_;
        }
        
        virtual ~Expression()
        {
        }
        
        virtual int accept(Visitor &) = 0;
        
    private:
        size_t lineNumber_;
    };
    
    class Expressions : public Expression {
    public:
        Expressions(ExpressionPtrs const &content) : Expression(0), content_(content)
        {
        }
        
        ExpressionPtrs const &content() const
        {
        return content_;
        }
        
    private:
        ExpressionPtrs content_;
    };
    
    class Program : public Expressions {
    public:
        Program(ExpressionPtrs const &content) : Expressions(content)
        {
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
    };
    
    class If : public Expressions {
    public:
        If(ExpressionPtr const &condition, ExpressionPtrs const &content) : Expressions(content), condition_(condition)
        {
        }
        
        int accept(Visitor &v)
        {
            return v.visit(*this);
        }
        
        ExpressionPtr Condition() const
        {
        return condition_;
        }
    private:
        ExpressionPtr condition_;
    };
    
    class While : public Expressions {
    public:
        While(ExpressionPtr const &condition, ExpressionPtrs const &content) : Expressions(content), condition_(condition)
        {
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
        
        ExpressionPtr Condition() const
        {
        return condition_;
        }
    private:
        ExpressionPtr condition_;
    };
    
    class FunctionDefinition : public Expressions {
    public:
        FunctionDefinition(std::string const& name, std::vector<std::string> params, ExpressionPtrs const &content) : Expressions(content), name_(name), params_(params)
        {
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
        
        std::string const& Name() const {
            return name_;
        }
        std::vector<std::string> const& Params() const
        {
        return params_;
        }
        
    private:
        std::string name_;
        std::vector<std::string> params_;
    };
    
    class Number : public Expression {
    public:
        Number(int value, size_t line) : Expression(line), value_(value)
        {
        }
        
        int Value() const
        {
        return value_;
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
        
    private:
        int value_;
    };
    
    class Read : public Expression {
    public:
        Read(std::string const &variable, size_t line) : Expression(line), variable_(variable)
        {
        }
        
        std::string Variable() const
        {
        return variable_;
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
        
    private:
        std::string variable_;
    };
    
    class Print : public Expression {
    public:
        Print(ExpressionPtr expression, size_t line) : Expression(line), expression_(expression)
        {
        }
        
        ExpressionPtr Expr() const
        {
        return expression_;
        }
        
        int accept(Visitor &v) {
            return v.visit(*this);
        }
        
    private:
        ExpressionPtr expression_;
    };
    
    class Return : public Expression {
    public:
        Return(ExpressionPtr expression, size_t line) : Expression(line), expression_(expression)
        {
        }
        
        ExpressionPtr Expr() const
        {
        return expression_;
        }
        
        int accept(Visitor &v) {
            return v.visit(*this);
        }
        
    private:
        ExpressionPtr expression_;
    };
    
    class BinaryExpression : public Expression {
    public:
        BinaryExpression(const char operation, ExpressionPtr left, ExpressionPtr right, size_t lineNumber) :
        Expression(lineNumber), operation_(operation), left_(left), right_(right) {
        }
        
        char Operation() const {
            return operation_;
        }
        
        ExpressionPtr Left() const {
            return left_;
        }
        
        ExpressionPtr Right() const {
            return right_;
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
    private:
        const char operation_;
        ExpressionPtr left_;
        ExpressionPtr right_;
    };
    
    class Condition : public Expression {
    public:
        Condition(std::string const& operation, ExpressionPtr left, ExpressionPtr right, size_t lineNumber) :
        Expression(lineNumber), operation_(operation), left_(left), right_(right) {
        }
        
        std::string const& Operation() const {
            return operation_;
        }
        
        ExpressionPtr Left() const {
            return left_;
        }
        
        ExpressionPtr Right() const {
            return right_;
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
    private:
        std::string operation_;
        ExpressionPtr left_;
        ExpressionPtr right_;
    };
    
    class Variable : public Expression {
    public:
        Variable(std::string const &variable, size_t line) : Expression(line), variable_(variable)
        {
        }
        
        std::string Name() const
        {
        return variable_;
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
        
    private:
        std::string variable_;
    };
    
    class VariableDefinition : public Expression {
    public:
        VariableDefinition(std::string const &name, ExpressionPtr const& expression, size_t line) : Expression(line), name_(name), expression_(expression)
        {
        }
        
        std::string Name() const
        {
        return name_;
        }
        
        ExpressionPtr Expr() const
        {
        return expression_;
        }
        
        int accept(Visitor &v) {
            return v.visit(*this);
        }
        
    private:
        std::string name_;
        ExpressionPtr expression_;
    };
    
    class Call : public Expression {
    public:
        Call(std::string const& name, ExpressionPtrs const &params, size_t line) : Expression(line), name_(name), params_(params)
        {
        }
        
        std::string const& Name() const {
            return name_;
        }
        
        ExpressionPtrs const& Params() const {
            return params_;
        }
        
        int accept(Visitor &v)
        {
        return v.visit(*this);
        }
        
    private:
        std::string name_;
        ExpressionPtrs params_;
    };
    
}

#endif /* end of include guard: AST_HPP */
