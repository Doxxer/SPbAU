#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <cstdio>

enum TokenType {
    // keywords
    def_,
    end_,
    print_,
    read_,
    if_,
    while_,
    return_,

    // id
    identifier_,
    number_,
    operator_,

    // other
    eof_
};

class Token {
public:
    virtual ~Token()
    {
    }

    virtual void PrintInfo() = 0;

    virtual TokenType GetType() = 0;
};

class TokenXXX : public Token {
public:
    explicit TokenXXX(char id) : id_(id)
    {
    }

    char GetID() const
    {
        return id_;
    }

    void PrintInfo()
    {
        printf("-- TokenXXX. ID = <%c>\n", id_);
    }

    TokenType GetType()
    {
        // TODO switch
        return operator_;
    }

private:
    char id_;
};

class TokenIdentifier : public Token {
public:
    TokenIdentifier(std::string id) : name_(id)
    {
    }

    std::string GetIdentifier() const
    {
        return name_;
    }

    void PrintInfo()
    {
        printf("-- TokenIdentifier. ID = <%s>\n", name_.c_str());
    }

    TokenType GetType()
    {
        return identifier_;
    }

private:
    std::string name_;
};

class TokenNumber : public Token {
public:
    explicit TokenNumber(int value) : value_(value)
    {
    }

    int GetValue() const
    {
        return value_;
    }

    void PrintInfo()
    {
        printf("-- TokenNumber. Value = <%d>\n", value_);
    }

    TokenType GetType()
    {
        return number_;
    }

private:
    int value_;
};

class TokenEOF : public Token {
public:
    void PrintInfo()
    {
        printf("-- TokenEOF\n");
    }

    TokenType GetType()
    {
        return eof_;
    }
};

#endif /* end of include guard: TOKEN_HPP */
