#include <iostream>
#include "Vector.hpp"

using std::cout;
using std::endl;

struct Verbose {
    Verbose(int data = 0) : data_(new int(data))
    {
        cout << "Verbose()" << endl;
    }

    ~Verbose()
    {
        cout << "~Verbose(), data = " << *data_ << endl;
        delete data_;
    }

    Verbose(Verbose const &other) : data_(new int(*other.data_))
    {
        cout << "Verbose(Verbose const &other)" << endl;
    }

    Verbose &operator=(Verbose const &other)
    {
        cout << "Verbose &operator=(Verbose const &other)" << endl;
        if (this != &other)
            Verbose(other).swap(*this);
        return *this;
    }

    void swap(Verbose &other)
    {
        std::swap(data_, other.data_);
    }

    int *data_;
};

template <typename T> void print_vector(Vector<T> const &v)
{
    for (size_t i = 0; i != v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;
}

template <> void print_vector(Vector<Verbose> const &v)
{
    for (size_t i = 0; i != v.size(); ++i)
        cout << *(v[i].data_) << " ";
    cout << endl;
}

void test_verbose()
{
    Vector<Verbose> v1;
    cout << "Vector v1 = ";
    print_vector(v1);

    for (int i = 0; i < 12; ++i) {
        v1.add(Verbose(i));
        cout << "v1.add(" << i << ") = ";
        print_vector(v1);
    }

    // Vector<Verbose> v2 = v1; //compile error

    Vector<Verbose> v3(v1);
    cout << "Vector v3 = ";
    print_vector(v3);

    v3.resize(10u);
    cout << "v3.resize(10u) = ";
    print_vector(v3);

    Vector<Verbose> v4;
    cout << "v4 = ";
    print_vector(v4);

    v4 = v3;

    cout << "v4 = ";
    print_vector(v4);

    cout << "v3 = ";
    print_vector(v3);
}

void test_int()
{
    Vector<int> v1;
    cout << "Vector v1 = ";
    print_vector(v1);

    for (int i = 0; i < 12; ++i) {
        v1.add(i);
        cout << "v1.add(" << i << ") = ";
        print_vector(v1);
    }

    // Vector<int> v2 = v1; //compile error

    Vector<int> v3(v1);
    cout << "Vector v3 = ";
    print_vector(v3);

    v3.resize(10u);
    cout << "v3.resize(10u) = ";
    print_vector(v3);

    Vector<int> v4;
    cout << "v4 = ";
    print_vector(v4);

    v4 = v3;

    cout << "v4 = ";
    print_vector(v4);

    cout << "v3 = ";
    print_vector(v3);
}

int main()
{
    test_verbose(); // ok
    test_int();     // ok
    return 0;
}
