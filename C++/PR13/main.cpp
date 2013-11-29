#include "Vector.hpp"
#include <iostream>

template <typename T> void print_vector(Vector<T> const &v)
{
    for (size_t i = 0; i != v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

int main()
{
    Vector<int> v1;
    std::cout << "Vector v1 = ";
    print_vector(v1);

    for (int i = 0; i < 6; ++i) {
        v1.add(i);
        std::cout << "v1.add(" << i << ") = ";
        print_vector(v1);
    }

    // Vector<int> v2 = v1; //compile error

    Vector<int> v3(v1);
    std::cout << "Vector v3 = ";
    print_vector(v3);

    v3.resize(10u);
    std::cout << "v3.resize(10u) = ";
    print_vector(v3);

    Vector<int> v4;
    std::cout << "v4 = ";
    print_vector(v4);

    v4 = v3;

    std::cout << "v4 = ";
    print_vector(v4);

    std::cout << "v3 = ";
    print_vector(v3);

    return 0;
}
