#ifndef AST_HPP
#define AST_HPP

#include <vector>

namespace AST {

class Expression {
public:
    virtual ~Expression()
    {
    }

    virtual int Process() = 0;

    virtual void Print(int level) = 0;
};

class Number : public Expression {
public:
    Number(int value) : value_(value)
    {
    }

    int Process()
    {
        return value_;
    }

    void Print(int level)
    {
        for (int i = 0; i < level; ++i)
            printf("-");
        printf("%d\n", value_);
    }

private:
    int value_;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(char op, Expression *lhs, Expression *rhs)
        : operator_(op), lhs_(lhs), rhs_(rhs)
    {
    }

    int Process()
    {
        int lvalue = lhs_->Process();
        int rvalue = rhs_->Process();

        switch (operator_) {
            case '+':
                return lvalue + rvalue;
            case '-':
                return lvalue - rvalue;
            case '*':
                return lvalue * rvalue;
            case '/':
                return lvalue / rvalue;
        }
        return 0;
    }

    void Print(int level)
    {
        lhs_->Print(level + 1);
        for (int i = 0; i < level; ++i)
            printf("-");
        printf("%c\n", operator_);
        rhs_->Print(level + 1);
    }

private:
    char operator_;
    Expression *lhs_, *rhs_;
};

class Variable : public Expression {
public:
    Variable(std::string const &name) : name_(name)
    {
    }

    int Process()
    {
        return 0;
    }

    void Print(int level)
    {
        for (int i = 0; i < level; ++i)
            printf("-");
        printf(" %s\n", name_.c_str());
    }

private:
    std::string name_;
};

class Call : public Expression {
public:
    Call(std::string const &name, std::vector<Expression *> &args) : name_(name), args_(args)
    {
    }

    int Process()
    {
        return -2;
    }

    void Print(int level)
    {
        for (int i = 0; i < level; ++i)
            printf("-");
        printf("Callee = %s\n", name_.c_str());
        for (size_t i = 0; i < args_.size(); ++i) {
            args_[i]->Print(level);
        }
    }

private:
    std::string name_;
    std::vector<Expression *> args_;
};

class FunctionPrototype {
public:
    FunctionPrototype(std::string const &name, std::vector<std::string> const &args)
        : name_(name), args_(args)
    {
    }

    void Print()
    {
        printf("name = <%s> Args: ", name_.c_str());
        for (size_t i = 0; i < args_.size(); ++i) {
            printf("%s, ", args_[i].c_str());
        }
    }

private:
    std::string name_;
    std::vector<std::string> args_;
};

class FunctionBody {
public:
    FunctionBody(FunctionPrototype *proto, Expression *body) : prototype_(proto), body_(body)
    {
    }

    void Print()
    {
        printf("Prototype: ");
        prototype_->Print();
        printf("\n");
        printf("Body:\n");
        body_->Print(0);
    }

private:
    FunctionPrototype *prototype_;
    Expression *body_;
};

inline Expression *Error(const char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    return 0;
}

inline FunctionPrototype *ErrorPrototype(const char *str)
{
    Error(str);
    return 0;
}

inline FunctionBody *ErrorFunction(const char *str)
{
    Error(str);
    return 0;
}
}

#endif /* end of include guard: AST_HPP */
