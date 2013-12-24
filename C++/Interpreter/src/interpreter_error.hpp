#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <cstddef>
#include <string>
#include <stdexcept>

class InterpreterError : public std::runtime_error {
public:
    explicit InterpreterError(size_t line, std::string const &message)
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

#endif
