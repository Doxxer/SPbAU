// template <class Arg, class Result> struct unary_function {
//     typedef Arg argument_type;
//     typedef Result result_type;
// };

template <class Arg1, class Arg2, class Result> struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;

    binary_function(result_type (*f)(first_argument_type, second_argument_type)) : f_ptr(f)
    {
    }

    result_type operator()(first_argument_type a, second_argument_type b) const
    {
        return f_ptr(a, b);
    }

protected:
    result_type (*f_ptr)(first_argument_type, second_argument_type);
};

template <class Operation>
class binder1st {
protected:
    Operation op;
    typename Operation::first_argument_type value;

public:
    binder1st(Operation const &x, const typename Operation::first_argument_type &y)
        : op(x), value(y)
    {
    }

    typename Operation::result_type
    operator()(const typename Operation::second_argument_type &x) const
    {
        return op(value, x);
    }
};

template <class Ret, class A1, class A2>
binder1st<binary_function<Ret, A1, A2> > bind1st(Ret (*f)(A1, A2), A2 const &x)
{
    typedef binary_function<Ret, A1, A2> fr;

    return binder1st<fr>(fr(f), x);
}
