#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

// struct base {
//     virtual void foo()
//     {
//         cout << "base::foo()" << endl;
//     }
// };
//
// struct derived : base {
//     void foo()
//     {
//         cout << "derived::foo()" << endl;
//     }
// };
//
//
// typedef void (*vptr_t)(base *);
// typedef vptr_t *vtrptable;

struct base {
    base(std::string const &s)
    {
        cout << "base ctor " << s << endl;
    }
};

struct base1 : virtual base {
    base1(std::string const &s) : base(s)
    {
    }
};

struct base2 : virtual base {
    base2(std::string const &s) : base(s)
    {
    }
};

struct derived : base1, base2 {
    derived() : base("a"), base1("b"), base2("c")
    {
    }
};

int main()
{
    // base *d = new derived();
    // base *b = new base();
    //
    // (**reinterpret_cast<vtrptable *>(d))(d);
    // (**reinterpret_cast<vtrptable *>(b))(b);
    
    derived a;
    return 0;
}
