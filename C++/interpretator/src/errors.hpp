#ifndef ERRORS_HPP
#define ERRORS_HPP

class LexerError : public std::runtime_error {
public:
    explicit LexerError(std::string const &message, size_t line)
    : std::runtime_error(message), line_(line)
    {
    }
    
    size_t line() const
    {
    return line_;
    }
    
private:
    size_t line_;
};

class ParserError : public std::runtime_error {
public:
    explicit ParserError(size_t line, std::string const &message = "")
    : std::runtime_error(message), line_(line)
    {
    }
    
    size_t line() const
    {
    return line_;
    }
    
private:
    size_t line_;
};

class RuntimeError : public std::runtime_error {
public:
    explicit RuntimeError(size_t line, std::string const &message = "")
    : std::runtime_error(message), line_(line)
    {
    }
    
    size_t line() const
    {
    return line_;
    }
    
private:
    size_t line_;
};

class UndefinedVariableError : public RuntimeError
{
public:
    explicit UndefinedVariableError(size_t line, std::string const &name)
    : RuntimeError(line, "undefined variable " + name){}
};

class UndefinedFunctionError : public RuntimeError
{
public:
    explicit UndefinedFunctionError(size_t line, std::string const &name)
    : RuntimeError(line, "undefined function " + name){}
};

class ArgumentsNumberMismatchError : public RuntimeError
{
public:
    explicit ArgumentsNumberMismatchError(size_t line, std::string const &name)
    : RuntimeError(line, "arguments number mismatch for " + name){}
};


class DivizionByZeroError : public RuntimeError
{
public:
    explicit DivizionByZeroError(size_t line)
    : RuntimeError(line, "divizion by zero"){}
};

#endif
