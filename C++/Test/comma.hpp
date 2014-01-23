#include <vector>

template <class T> class make_vector {
    std::vector<T> data;

public:
    make_vector(T const &val)
    {
        data.push_back(val);
    }

    make_vector<T> &operator, (T const &t)
    {
        data.push_back(t);
        return *this;
    }

    operator std::vector<T>()
    {
        return data;
    }
};

template <class T> make_vector<T> makeVect(T const &t)
{
    return make_vector<T>(t);
}
