#ifndef STACK_HPP
#define STACK_HPP

#include <cassert>

#include "array.hpp"

template <typename T, size_t N, template <typename, size_t> class Container = Array> class Stack {
public:
    Stack() : top_index_(0)
    {
    }

    void push(T const &value)
    {
        assert(!full());
        data_[top_index_++] = value;
    }

    T const &top() const
    {
        assert(!empty());
        return data_[top_index_ - 1];
    }

    void pop()
    {
        assert(!empty());
        --top_index_;
    }

    bool empty() const
    {
        return top_index_ == 0;
    }

    bool full() const
    {
        return top_index_ == N;
    }

    size_t size() const
    {
        return top_index_;
    }

private:
    size_t top_index_;
    Container<T, N> data_;
};

#endif /* end of include guard: STACK_HPP */
