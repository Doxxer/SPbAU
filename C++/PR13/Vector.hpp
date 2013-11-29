#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>

template <typename T> class Vector {
public:
    explicit Vector(size_t initialSize = 0, T const &value = T())
        : increase_factor_(2.0),
          size_(initialSize),
          capacity_(std::max(initialSize, 16ul)),
          data_(new T[capacity_])
    {
        std::fill(data_, data_ + size_, value);
    }

    explicit Vector(Vector const &other)
        : increase_factor_(2.0),
          size_(other.size_),
          capacity_(other.capacity_),
          data_(new T[capacity_])
    {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    ~Vector()
    {
        delete[] data_;
    }

    Vector &operator=(Vector const &other)
    {
        if (this != &other)
            Vector(other).swap(*this);
        return *this;
    }

    void add(T const &value)
    {
        reserve(size_ + 1);
        data_[size_++] = value;
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity > capacity_) {
            newCapacity = std::max(newCapacity, (size_t)(capacity_ * increase_factor_));
            T *temp = new T[newCapacity];
            std::copy(data_, data_ + size_, temp);
            delete[] data_;
            data_ = temp;
            capacity_ = newCapacity;
        }
    }

    void resize(size_t newSize)
    {
        reserve(newSize);
        std::fill(data_ + size_, data_ + newSize, 0u);
        size_ = newSize;
    }

    T &operator[](size_t i)
    {
        return data_[i];
    }
    T const &operator[](size_t i) const
    {
        return data_[i];
    }

    size_t size() const
    {
        return size_;
    }

    void swap(Vector<T> &other)
    {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

private:
    const float increase_factor_;
    size_t size_;
    size_t capacity_;
    T *data_;
};

#endif /* end of include guard: VECTOR_H */
