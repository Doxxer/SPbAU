#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T, size_t N> class Array {
public:
    Array()
    {
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
