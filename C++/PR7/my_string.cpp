#include "my_string.hpp"
#include <cstring>
#include <algorithm>

my_string::my_string() : data_(new char[1])
{
    data_[0] = '\0';
}

my_string::my_string(char const *const str) : data_(new char[strlen(str) + 1])
{
    strcpy(data_, str);
}

my_string::my_string(my_string const &str) : data_(new char[str.length() + 1])
{
    strcpy(data_, str.c_str());
}

my_string::~my_string()
{
    delete[] data_;
}

my_string &my_string::operator=(my_string const &str)
{
    if (this != &str) {
        my_string(str).swap(*this);
    }
    return *this;
}

my_string &my_string::append(my_string const &str)
{
    char *data = new char[length() + str.length() + 1];
    strcpy(data, data_);
    strcat(data, str.c_str());

    delete[] data_;
    data_ = data;
    return *this;
}

void my_string::swap(my_string &str)
{
    std::swap(data_, str.data_);
}

size_t my_string::length() const
{
    return strlen(data_);
}
