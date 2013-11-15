#include <cstddef>
#include <iostream>

template <typename T> struct unique_ptr_ref {
    T *data_;

    explicit unique_ptr_ref(T *a) : data_(a)
    {
    }
};

template <typename T> struct default_delete {
    default_delete()
    {
    }

    void operator()(T *a)
    {
        delete a;
    }
};

template <typename T, typename D = default_delete<T> > class unique_ptr {
public:
    unique_ptr(T *pointer, D deleter = default_delete<T>()) : data_(pointer), deleter_(deleter)
    {
    }

    ~unique_ptr()
    {
        delete_data();
    }

    unique_ptr(unique_ptr &a) : data_(a.release())
    {
    }

    unique_ptr(unique_ptr_ref<T> ref) : data_(ref.data_)
    {
    }

    unique_ptr &operator=(unique_ptr &a)
    {
        reset(a.release());
        return *this;
    }

    template <typename T1> operator unique_ptr_ref<T1>()
    {
        return unique_ptr_ref<T1>(this->release());
    }

    T *release()
    {
        T *temp = data_;
        data_ = NULL;
        return temp;
    }

    void reset(T *pointer = NULL)
    {
        if (pointer != data_) {
            delete_data();
            data_ = pointer;
        }
    }

    operator bool() const
    {
        return data_ != NULL;
    }

    T *operator->() const
    {
        return data_;
    }

    T &operator*() const
    {
        return *data_;
    }

private:
    T *data_;
    D deleter_;

    void delete_data()
    {
        deleter_(data_);
    }
};
