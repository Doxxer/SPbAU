#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>

template <typename T, size_t N> class Array {
public:
    Array(T const &initial_value = T())
    {
        std::fill(data_, data_ + N, initial_value);
    }

    size_t size() const
    {
        return N;
    }

    T const &operator[](size_t index) const
    {
        assert(index < N);
        return data_[index];
    }

    T &operator[](size_t index)
    {
        assert(index < N);
        return data_[index];
    }

private:
    T data_[N];
};

#endif /* end of include guard: ARRAY_HPP */
