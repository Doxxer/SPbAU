template <class Ret, class A1, class A2> class binder1st {
private:
    Ret (*f_ptr)(A1, A2);
    A1 value;

public:
    binder1st(Ret (*f)(A1, A2), A1 const &x) : f_ptr(f), value(x)
    {
    }

    Ret operator()(A2 const &y) const
    {
        return f_ptr(value, y);
    }
};

template <class Ret, class A1, class A2>
binder1st<Ret, A1, A2> bind1st(Ret (*f)(A1, A2), A2 const &x)
{
    return binder1st<Ret, A1, A2>(f, x);
}
