#ifndef STACK_HPP
#define STACK_HPP

#include "array.hpp"

template <typename T, size_t N, template <typename, size_t> class Container = Array> class Stack {
public:
    Stack() : top_index_(0)
    {
    }

    void push(T const &value)
    {
        if (!full())
            data_[top_index_++] = value;
        else
            std::cerr << "stack is full" << std::endl;
    }

    T top() const
    {
        if (!empty())
            return data_[top_index_ - 1];
        else {
            std::cerr << "stack is empty" << std::endl; // exception should be
            return 0;
        }
    }

    void pop()
    {
        if (!empty())
            --top_index_;
        else
            std::cerr << "stack is empty" << std::endl;
    }

    bool empty() const
    {
        return top_index_ == 0;
    }

    bool full() const
    {
        return top_index_ == N;
    }

private:
    size_t top_index_;
    Container<T, N> data_;
};

#endif /* end of include guard: STACK_HPP */
