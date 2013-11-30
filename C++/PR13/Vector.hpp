#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>

template <typename T> class Vector {
public:
    explicit Vector() : increase_factor_(2.0), size_(0), capacity_(4ul), data_(allocate(capacity_))
    {
    }

    explicit Vector(size_t initialSize, T const &value = T())
        : increase_factor_(2.0),
          size_(initialSize),
          capacity_(std::max(initialSize, 4ul)),
          data_(allocate(capacity_))
    {
        for (size_t i = 0; i < size_; ++i) {
            new (data_ + i) T(value);
        }
    }

    explicit Vector(Vector const &other)
        : increase_factor_(2.0),
          size_(other.size_),
          capacity_(other.capacity_),
          data_(allocate(capacity_))
    {
        copy(other.data_, size_, data_);
    }

    ~Vector()
    {
        deallocate();
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
        new (data_ + size_++) T(value);
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity > capacity_) {
            newCapacity = std::max(newCapacity, (size_t)(capacity_ * increase_factor_));

            T *temp = allocate(newCapacity);
            copy(data_, size_, temp);
            deallocate();

            data_ = temp;
            capacity_ = newCapacity;
        }
    }

    void resize(size_t newSize)
    {
        reserve(newSize);
        for (size_t i = size_; i < newSize; ++i) {
            new (data_ + i) T();
        }
        for (size_t i = newSize; i < size_; ++i) {
            data_[i].~T();
        }
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

    T *allocate(size_t size)
    {
        return (T *)::operator new[](size * sizeof(T));
    }

    void deallocate()
    {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        ::operator delete[](data_);
    }

    void copy(T *source, size_t count, T *destination)
    {
        for (size_t i = 0; i < count; ++i) {
            new (destination + i) T(source[i]);
        }
    }
};

#endif /* end of include guard: VECTOR_H */
