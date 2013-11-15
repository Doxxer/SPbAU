#include "unique_ptr.cpp"
#include <iostream>

class Foo {
public:
    Foo(int a = 0) : a_(a)
    {
        std::cout << "Foo\n";
    }
    ~Foo()
    {
        std::cout << "~Foo " << a_ << std::endl;
    }
    void bar()
    {
        std::cout << ++a_ << std::endl;
    }

private:
    int a_;
};

unique_ptr<Foo> func()
{
    unique_ptr<Foo> p1(new Foo(15));
    return p1;
}

struct Deleter {
    void operator()(Foo *p) const
    {
        std::cout << "Delete Foo object\n";
        delete p;
    }
};

int main()
{
    unique_ptr<Foo, Deleter> ptr(new Foo(7), Deleter());
    ptr.reset(new Foo(1000));

    unique_ptr<Foo> p1(new Foo);
    if (p1)
        p1->bar();

    {
        unique_ptr<Foo> temp = func();
        temp->bar();
    }
    unique_ptr<Foo> p2 = p1;

    if (p1)
        p1->bar();

    return 0;
}
