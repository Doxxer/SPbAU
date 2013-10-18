#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstddef>

class my_string {
public:
    my_string();
    my_string(char const *const str);
    my_string(my_string const &str);
    ~my_string();

    my_string &operator=(my_string const &str);

    my_string &append(my_string const &str);

    void swap(my_string &str);

    char at(size_t it) const
    {
        return data_[it];
    }

    char &at(size_t it)
    {
        return data_[it];
    }

    char const *c_str() const
    {
        return data_;
    }

    size_t length() const;
    
private:
    char *data_;
};

#endif /* end of include guard: MY_STRING_HPP */
