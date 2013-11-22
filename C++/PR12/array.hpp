#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <vector>

using std::vector;

template <typename T, size_t N> class Array {
public:
    explicit Array(T initial_value = 0) : data_(vector<T>(N, initial_value))
    {
    }

    ~Array()
    {
    }

    size_t size() const
    {
        return N;
    }

    T operator[](size_t index) const
    {
        return data_[index];
    }

    T &operator[](size_t index)
    {
        return data_[index];
    }

private:
    vector<T> data_;
};

#endif /* end of include guard: ARRAY_HPP */
