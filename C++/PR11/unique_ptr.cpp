#include <cstddef>
#include <iostream>

template <typename T, typename D> struct unique_ptr_ref {
    T *data_;
    D deleter_;

    unique_ptr_ref(T *a, D deleter) : data_(a), deleter_(deleter)
    {
    }
};

template <typename T> struct default_delete {
    void operator()(T *a)
    {
        delete a;
    }
};

template <typename T, typename D = default_delete<T> > class unique_ptr {
public:
    unique_ptr(T *pointer, D deleter = D()) : data_(pointer), deleter_(deleter)
    {
    }

    ~unique_ptr()
    {
        reset();
    }

    unique_ptr(unique_ptr &a) : data_(a.release()), deleter_(a.deleter_)
    {
    }

    template <typename T1, typename D1>
    unique_ptr(unique_ptr<T1, D1> &a)
        : data_(a.release()), deleter_(a.deleter_)
    {
    }

    unique_ptr &operator=(unique_ptr &a)
    {
        reset(a.release());
        deleter_ = a.deleter_;
        return *this;
    }

    unique_ptr &operator=(unique_ptr_ref<T, D> ref)
    {
        reset(ref.data_);
        deleter_ = ref.deleter_;
        return *this;
    }

    template <typename T1> unique_ptr &operator=(unique_ptr<T1, D> &a)
    {
        reset(a.release());
        deleter_ = a.deleter_;
        return *this;
    }

    unique_ptr(unique_ptr_ref<T, D> ref) : data_(ref.data_), deleter_(ref.deleter_)
    {
    }

    template <typename T1> operator unique_ptr_ref<T1, D>()
    {
        return unique_ptr_ref<T1, D>(this->release(), deleter_);
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
            deleter_(data_);
            data_ = pointer;
        }
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
};
