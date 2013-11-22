#include "unique_ptr.hpp"
#include <iostream>
#include <stdlib.h>

unique_ptr<int> new_int()
{
    return unique_ptr<int>(new int(10));
}

template <typename T> struct array_deleter {
    void operator()(T *a)
    {
        delete[] a;
    }
};

unique_ptr<int, array_deleter<int> > new_int_array()
{
    return unique_ptr<int, array_deleter<int> >(new int[10]);
}

unique_ptr<int, void (*)(void *)> malloc_int()
{
    return unique_ptr<int, void (*)(void *)>((int *)malloc(sizeof(int)), &free);
}

int main()
{
    unique_ptr<int> v1 = new_int();

    unique_ptr<int, array_deleter<int> > v2 = new_int_array();
    unique_ptr<int, void (*)(void *)> v3 = malloc_int();
    v1.reset(NULL);                
    std::cout << *v3 << std::endl;
    return 0;
}
