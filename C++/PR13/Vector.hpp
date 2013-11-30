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
        fill(data_, size_, 0, value);
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
        place(data_, size_++, value);
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

        if (newSize > size_)
            fill(data_, newSize - size_, size_);
        else
            release(data_, size_ - newSize, newSize);

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
        return (T *)::operator new(size * sizeof(T));
    }

    void deallocate()
    {
        release(data_, size_);
        ::operator delete(data_);
    }

    void place(T *memory, size_t index, T const &value = T())
    {
        new (memory + index) T(value);
    }

    void release(T *memory, size_t count, size_t start_index = 0)
    {
        for (size_t i = 0; i < count; ++i) {
            memory[start_index + i].~T();
        }
    }

    void copy(T *source, size_t count, T *destination)
    {
        for (size_t i = 0; i < count; ++i) {
            place(destination, i, source[i]);
        }
    }

    void fill(T *destination, size_t count, size_t start_index = 0, T const &value = T())
    {
        for (size_t i = 0; i < count; ++i) {
            place(destination, start_index + i, value);
        }
    }
};

#endif /* end of include guard: VECTOR_H */
